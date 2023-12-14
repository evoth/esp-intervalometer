#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"

extern char apiUrl[64];
extern bool cameraConnected;

extern void cameraConnect(DynamicJsonDocument doc);
extern void triggerShutter();

#endif