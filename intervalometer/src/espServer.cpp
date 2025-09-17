#include "espServer.h"
#include <TimeLib.h>
#include "camera.h"
#include "clock.h"
#include "resources.h"
#include "status.h"

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
  status["cameraConnected"] = intervalometer.camera.connected;
  status["cameraIP"] = intervalometer.camera.cameraIP;
  status["intervalSec"] = intervalometer.intervalSec;
  status["isRunning"] = intervalometer.isRunning;
  status["numShots"] = intervalometer.numShots;
  status["timeUntilNext"] = intervalometer.timeUntilNext();
  status["timeUntilCompletion"] = intervalometer.timeUntilCompletion();
  status["shutterIsPressed"] = intervalometer.camera.shutterIsPressed;
  status["actions"] = intervalometer.actions;
  status["actionIndex"] = intervalometer.actionIndex;
  String statusText;
  serializeJson(status, statusText);
  Serial.println(statusText);
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
            if (!deserializeJson(msg, (const char*)payload)) {
              newMsg = true;
            }
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
void ESPServer::processRequest() {
  if (!newMsg)
    return;

  String command = msg["command"];

  if (command == "setTime") {
    setEspTime(msg);
  } else if (command == "connect") {
    intervalometer.camera.connect(msg);
  } else if (command == "start") {
    intervalometer.start(msg);
  } else if (command == "stop") {
    intervalometer.stop();
  } else if (command == "triggerShutter") {
    intervalometer.camera.triggerShutter();
  } else if (command == "pressShutter") {
    intervalometer.camera.pressShutter();
  } else if (command == "releaseShutter") {
    intervalometer.camera.releaseShutter();
  } else if (command == "triggerIR") {
    intervalometer.ir.trigger();
  } else {
    statusCode = 0;
    snprintf(statusMsg, sizeof(statusMsg), "Unknown command.");
  }

  sendStatus();
  newMsg = false;
}

void ESPServer::loop() {
  if (Serial.available()) {
    String json = Serial.readStringUntil('\n');
    if (!deserializeJson(msg, json)) {
      newMsg = true;
    }
  }
  processRequest();
  intervalometer.loop();
}