#ifndef ESP_INT_CLOCK_H
#define ESP_INT_CLOCK_H

#include <ArduinoJson.h>

extern void setEspTime(JsonDocument doc);

extern unsigned long millisecond();
extern unsigned long msOffset;

#endif
