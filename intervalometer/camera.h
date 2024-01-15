#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"

extern char cameraIP[32];
extern bool cameraConnected;
extern bool bulbMode;

extern void cameraConnect(DynamicJsonDocument doc);
extern void getBulb();
extern void triggerShutter();
extern void pressShutter();
extern void releaseShutter();
extern void enableBulb();
extern void disableBulb();
extern float parseExpSetting();

#endif