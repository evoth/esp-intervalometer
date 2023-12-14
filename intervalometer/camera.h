#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"

extern char cameraIP[32];
extern bool cameraConnected;

extern void cameraConnect(DynamicJsonDocument doc);
extern void triggerShutter();

#endif