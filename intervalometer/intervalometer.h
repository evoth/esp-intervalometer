#ifndef INTERVALOMETER_H
#define INTERVALOMETER_H

#include "camera.h"
#include "server.h"

extern int intervalSec;
extern int numShots;
extern bool isRunning;

extern void startIntervalometer(DynamicJsonDocument doc);
extern void stopIntervalometer();
extern void getIntervalometerStatus(AsyncWebServerRequest *request);
extern void loopIntervalometer();

#endif