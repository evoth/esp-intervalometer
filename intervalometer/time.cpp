#include "time.h"

unsigned long msOffset = 0;

unsigned long millisecond() {
  return (millis() + msOffset) % 1000;
}

// Sets internal clock from "sec" since epoch and "ms" milliseconds
void set_time(AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total) {
  DynamicJsonDocument doc(64);
  deserializeJson(doc, data);
  time_t t = doc["sec"];
  setTime(t);
  unsigned long ms = doc["ms"];
  msOffset = (1000 + ms - (millis() % 1000)) % 1000;
  String response;
  serializeJson(doc, response);
  req->send(200, "application/json", response);
}

// Gets internal time in "sec" since epoch and "ms" milliseconds
void get_time(AsyncWebServerRequest *req){
  DynamicJsonDocument doc(64);
  doc["sec"] = now();
  doc["ms"] = millisecond();
  String response;
  serializeJson(doc, response);
  req->send(200, "application/json", response);
}