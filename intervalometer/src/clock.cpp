#include "clock.h"
#include "status.h"
#include <Arduino.h>
#include <TimeLib.h>

unsigned long msOffset = 0;

unsigned long millisecond() {
  return (millis() + msOffset) % 1000;
}

// Sets internal clock from "sec" since epoch and "ms" milliseconds
void setEspTime(JsonDocument doc) {
  time_t t = doc["sec"];
  setTime(t);
  unsigned long ms = doc["ms"];
  msOffset = (1000 + ms - (millis() % 1000)) % 1000;

  statusCode = 200;
  snprintf(statusMsg, sizeof(statusMsg), "ESP8266 clock set successfully.");
}