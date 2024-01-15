#ifndef INTERVALOMETER_H
#define INTERVALOMETER_H

#include "camera.h"
#include "server.h"

extern float intervalSec;
extern float bulbSec;
extern int numShots;
extern bool isRunning;

extern unsigned long timeUntilNext();
extern unsigned long timeUntilRelease();
extern void startIntervalometer(DynamicJsonDocument doc);
extern void stopIntervalometer();
extern void loopIntervalometer();

#endif