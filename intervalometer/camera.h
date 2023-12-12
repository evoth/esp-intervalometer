#ifndef CAMERA_H
#define CAMERA_H

#include <ArduinoJson.h>

#include "global.h"

extern bool cameraConnected;
extern int errorCode;
extern char errorMsg[256];

extern void cameraConnect(AsyncWebServerRequest *request, DynamicJsonDocument doc);
extern void triggerShutter();

#endif