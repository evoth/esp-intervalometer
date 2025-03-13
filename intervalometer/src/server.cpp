#include "server.h"
#include <ESPAsyncWebServer.h>
#include <TimeLib.h>
#include "camera.h"
#include "clock.h"
#include "intervalometer.h"
#include "resources.h"
#include "status.h"
// ENABLE ASYNC MODE IN WebSockets.h TO AVOID BLOCKING
#include <WebSocketsServer.h>

void ESPServer::initAP() {
  const char* ssid = "ESP8266_AP";
  const char* password = "defgecd7";

  Serial.print("Starting soft-AP... ");
  WiFi.softAP(ssid, password);

  Serial.print("Soft-AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void ESPServer::initWebServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* req) {
    req->send_P(200, "text/html", indexHtml);
  });

  server.on("/icon.svg", HTTP_GET, [](AsyncWebServerRequest* req) {
    req->send_P(200, "image/svg+xml", iconSvg);
  });

  server.onNotFound([](AsyncWebServerRequest* req) {
    if (req->method() == HTTP_OPTIONS) {
      // CORS OPTIONS request
      req->send(200);
    } else {
      req->send(404, "text/plain", "Not found");
    }
  });

  // CORS OPTIONS request
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials",
                                       "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods",
                                       "GET,HEAD,OPTIONS,POST,PUT");
  DefaultHeaders::Instance().addHeader(
      "Access-Control-Allow-Headers",
      "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, "
      "Content-Type, Access-Control-Request-Method, "
      "Access-Control-Request-Headers");

  server.begin();
}

void ESPServer::sendStatus() {
  JsonDocument status;
  status["statusCode"] = statusCode;
  status["statusMsg"] = statusMsg;
  status["sec"] = now();
  status["ms"] = millisecond();
  status["cameraConnected"] = cameraConnected;
  status["cameraIP"] = cameraIP;
  status["intervalSec"] = intervalometer.intervalSec;
  status["isRunning"] = intervalometer.isRunning;
  status["numShots"] = intervalometer.numShots;
  status["timeUntilNext"] = intervalometer.timeUntilNext();
  status["bulbMode"] = bulbMode;
  status["bulbSec"] = intervalometer.bulbSec;
  status["timeUntilRelease"] = intervalometer.timeUntilRelease();
  status["timeUntilCompletion"] = intervalometer.timeUntilCompletion();
  status["shutterIsPressed"] = shutterIsPressed;
  String statusText;
  serializeJson(status, statusText);
  webSocket.broadcastTXT(statusText);
}

void ESPServer::initWebSocketServer() {
  webSocket.begin();
  webSocket.onEvent(
      [this](uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
        switch (type) {
          case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
          case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num,
                          ip[0], ip[1], ip[2], ip[3], payload);
            sendStatus();
          } break;
          case WStype_TEXT:
            newMsg = true;
            deserializeJson(msg, (const char*)payload);
            break;
          default:
            break;
        }
      });
}

void ESPServer::initServer() {
  initAP();
  initWebServer();
  initWebSocketServer();
}

// Execute command based on most recent WebSocket message
void ESPServer::loopProcessRequest() {
  if (!newMsg)
    return;

  String command = msg["command"];

  if (command == "setTime") {
    setEspTime(msg);
  } else if (command == "connect") {
    cameraConnect(msg);
    getBulb();
  } else if (command == "start") {
    intervalometer.start(msg);
  } else if (command == "stop") {
    intervalometer.stop();
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

void ESPServer::loop() {
  loopProcessRequest();
  intervalometer.loop();
}