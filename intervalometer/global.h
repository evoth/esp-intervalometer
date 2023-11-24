#ifndef GLOBAL_H
#define GLOBAL_H

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncUDP.h>
#include <ESP8266HTTPClient.h>

extern AsyncWebServer server;
extern AsyncUDP udp;
extern WiFiClient client;
extern HTTPClient http;

#endif