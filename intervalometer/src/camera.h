#ifndef ESP_INT_CAMERA_H
#define ESP_INT_CAMERA_H

#include <ArduinoJson.h>

class Camera {
 public:
  char cameraIP[32];
  bool connected = false;
  bool bulbMode = false;
  bool shutterIsPressed = false;

  void connect(JsonDocument doc);
  void getBulb();
  void triggerShutter();
  void pressShutter();
  void releaseShutter();
  void enableBulb();
  void disableBulb();
  float parseExpSetting();

 private:
  char apiUrl[64];
  char expSetting[16];
  const char* apiUrlTemplate = "http://%s:8080/ccapi";

  void request(const char* url,
               std::function<int()> action,
               std::function<void()> success,
               std::function<void()> failure);
};

#endif
