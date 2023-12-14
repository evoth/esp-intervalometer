#include "global.h"

AsyncWebServer server(80);
WiFiClient client;
HTTPClient http;
WebSocketsServer webSocket = WebSocketsServer(81);

int statusCode = 0;
char statusMsg[256] = "ESP8266 booted.";