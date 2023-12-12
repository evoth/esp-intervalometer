#ifndef INTERVALOMETER_H
#define INTERVALOMETER_H

#include "camera.h"

extern void startIntervalometer(AsyncWebServerRequest *request, DynamicJsonDocument doc);
extern void stopIntervalometer(AsyncWebServerRequest *request);
extern void getIntervalometerStatus(AsyncWebServerRequest *request);
extern void loopIntervalometer();

#endif