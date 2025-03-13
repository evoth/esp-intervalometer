#ifndef ESP_INT_SERVER_H
#define ESP_INT_SERVER_H

#include "intervalometer.h"

class ESPServer {
 public:
  ESPServer()
      : server(80), webSocket(81), intervalometer([this]() { sendStatus(); }) {}

  void initServer();
  void loop();
  void sendStatus();

 private:
  AsyncWebServer server;
  WebSocketsServer webSocket;
  JsonDocument msg;
  bool newMsg = false;
  Intervalometer intervalometer;

  void initAP();
  void initWebServer();
  void initWebSocketServer();
  void loopProcessRequest();
};

#endif
