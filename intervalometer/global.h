#ifndef GLOBAL_H
#define GLOBAL_H

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

extern AsyncWebServer server;
extern WiFiClient client;
extern HTTPClient http;
extern WebSocketsServer webSocket;

extern int statusCode;
extern char statusMsg[256];

#endif