#ifndef INTERVALOMETER_H
#define INTERVALOMETER_H

#include "camera.h"
#include "server.h"

extern int intervalSec;
extern int numShots;
extern bool isRunning;

extern unsigned long timeUntilNext();
extern void startIntervalometer(DynamicJsonDocument doc);
extern void stopIntervalometer();
extern void loopIntervalometer();

#endif