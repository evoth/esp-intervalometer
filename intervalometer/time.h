#ifndef TIME_H
#define TIME_H

#include <ESPAsyncWebServer.h>
#include <TimeLib.h>
#include <ArduinoJson.h>

extern void set_time(AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total);
extern void get_time(AsyncWebServerRequest *req);

extern unsigned long millisecond();
extern unsigned long msOffset;

#endif