#include "server.h"

DynamicJsonDocument msg(1024);
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
    req->send(200, "text/html", index_html);
  });

  server.on("/icon.svg", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "image/svg+xml", icon_svg);
  });

  server.onNotFound([](AsyncWebServerRequest *req){
    if (req->method() == HTTP_OPTIONS) {
      req->send(200);
    } else {
      req->send(404, "text/plain", "Not found");
    }
  });

  // CORS
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");

  server.begin();
}

void sendStatus() {
  DynamicJsonDocument status(1024);
  status["statusCode"] = statusCode;
  status["statusMsg"] = statusMsg;
  status["sec"] = now();
  status["ms"] = millisecond();
  status["cameraConnected"] = cameraConnected;
  status["cameraIP"] = cameraIP;
  status["intervalSec"] = intervalSec;
  status["isRunning"] = isRunning;
  status["numShots"] = numShots;
  String statusText;
  serializeJson(status, statusText);
  Serial.print("Sending status... ");
  webSocket.broadcastTXT(statusText);
  Serial.println("Sent.");
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
      Serial.printf("[%u] get Text: %s\n", num, payload);
      newMsg = true;
      deserializeJson(msg, (const char*) payload);
      break;
  }
}

void initWebSockerServer() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void initServer() {
  initAP();
  initWebServer();
  initWebSockerServer();
}

void loopProcessRequest() {
  if (!newMsg) return;

  String command = msg["command"];

  char bodyText[1024];
  serializeJson(msg["body"], bodyText);
  DynamicJsonDocument body(1024);
  deserializeJson(body, bodyText);

  if (command == "setTime") {
    setEspTime(body);
  } else if (command == "connect") {
    cameraConnect(body);
  } else if (command == "start") {
    startIntervalometer(body);
  } else if (command == "stop") {
    stopIntervalometer();
  } else {
    statusCode = 0;
    snprintf(statusMsg, sizeof(statusMsg), "Unknown command.");
  }

  sendStatus();
  newMsg = false;
}