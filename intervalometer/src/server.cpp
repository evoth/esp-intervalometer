#include "server.h"
#include "status.h"
#include "resources.h"
#include "clock.h"
#include "camera.h"
#include "intervalometer.h"
#include <TimeLib.h>
#include <ESPAsyncWebServer.h>
// ENABLE ASYNC MODE IN WebSockets.h TO AVOID BLOCKING
#include <WebSocketsServer.h>

AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
JsonDocument msg;
bool newMsg = false;

void initAP()
{
  const char *ssid = "ESP8266_AP";
  const char *password = "defgecd7";

  Serial.print("Starting soft-AP... ");
  WiFi.softAP(ssid, password);

  Serial.print("Soft-AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void initWebServer()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send_P(200, "text/html", indexHtml);
  });

  server.on("/icon.svg", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send_P(200, "image/svg+xml", iconSvg);
  });

  server.onNotFound([](AsyncWebServerRequest *req){
    if (req->method() == HTTP_OPTIONS) {
      // CORS OPTIONS request
      req->send(200);
    } else {
      req->send(404, "text/plain", "Not found");
    }
  });

  // CORS OPTIONS request
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");

  server.begin();
}

void sendStatus() {
  JsonDocument status;
  status["statusCode"] = statusCode;
  status["statusMsg"] = statusMsg;
  status["sec"] = now();
  status["ms"] = millisecond();
  status["cameraConnected"] = cameraConnected;
  status["cameraIP"] = cameraIP;
  status["intervalSec"] = intervalSec;
  status["isRunning"] = isRunning;
  status["numShots"] = numShots;
  status["timeUntilNext"] = timeUntilNext();
  status["bulbMode"] = bulbMode;
  status["bulbSec"] = bulbSec;
  status["timeUntilRelease"] = timeUntilRelease();
  status["timeUntilCompletion"] = timeUntilCompletion();
  status["shutterIsPressed"] = shutterIsPressed;
  String statusText;
  serializeJson(status, statusText);
  webSocket.broadcastTXT(statusText);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        sendStatus();
      }
      break;
    case WStype_TEXT:
      newMsg = true;
      deserializeJson(msg, (const char*) payload);
      break;
    default:
      break;
  }
}

void initWebSocketServer() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void initServer() {
  initAP();
  initWebServer();
  initWebSocketServer();
}

// Execute command based on most recent WebSocket message
void loopProcessRequest() {
  if (!newMsg) return;

  String command = msg["command"];

  if (command == "setTime") {
    setEspTime(msg);
  } else if (command == "connect") {
    cameraConnect(msg);
    getBulb();
  } else if (command == "start") {
    startIntervalometer(msg);
  } else if (command == "stop") {
    stopIntervalometer();
  } else if (command == "enableBulb") {
    enableBulb();
  } else if (command == "disableBulb") {
    disableBulb();
  } else if (command == "triggerShutter") {
    triggerShutter();
  } else if (command == "pressShutter") {
    pressShutter();
  } else if (command == "releaseShutter") {
    releaseShutter();
  } else {
    statusCode = 0;
    snprintf(statusMsg, sizeof(statusMsg), "Unknown command.");
  }

  sendStatus();
  newMsg = false;
}