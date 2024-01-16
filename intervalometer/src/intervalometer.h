#ifndef ESP_INT_INTERVALOMETER_H
#define ESP_INT_INTERVALOMETER_H

#include <ArduinoJson.h>

extern float intervalSec;
extern float bulbSec;
extern int numShots;
extern bool isRunning;

extern unsigned long timeUntilNext();
extern unsigned long timeUntilRelease();
extern void startIntervalometer(JsonDocument doc);
extern void stopIntervalometer();
extern void loopIntervalometer();

#endif
