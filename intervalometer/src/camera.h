#ifndef ESP_INT_CAMERA_H
#define ESP_INT_CAMERA_H

#include <ArduinoJson.h>

extern char cameraIP[32];
extern bool cameraConnected;
extern bool bulbMode;

extern void cameraConnect(JsonDocument doc);
extern void getBulb();
extern void triggerShutter();
extern void pressShutter();
extern void releaseShutter();
extern void enableBulb();
extern void disableBulb();
extern float parseExpSetting();

#endif
