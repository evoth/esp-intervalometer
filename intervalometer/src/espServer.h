#ifndef ESP_INT_SERVER_H
#define ESP_INT_SERVER_H

#include <ESPAsyncWebServer.h>
// ENABLE ASYNC MODE IN WebSockets.h TO AVOID BLOCKING
#include <WebSocketsServer.h>
#include "intervalometer.h"

class ESPServer {
 public:
  ESPServer()
      : intervalometer([this]() { sendStatus(); }), server(80), webSocket(81) {}

  void initServer();
  void loop();
  void sendStatus();

 private:
  Intervalometer intervalometer;
  AsyncWebServer server;
  WebSocketsServer webSocket;
  JsonDocument msg;
  bool newMsg = false;

  void initAP();
  void initWebServer();
  void initWebSocketServer();
  void processRequest();
};

#endif
