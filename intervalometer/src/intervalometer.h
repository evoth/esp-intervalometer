#ifndef ESP_INT_INTERVALOMETER_H
#define ESP_INT_INTERVALOMETER_H

#include <ArduinoJson.h>
#include <functional>
#include "camera.h"

class Intervalometer {
 public:
  Intervalometer(std::function<void()> sendStatus) : sendStatus(sendStatus) {}

  Camera camera;
  float intervalSec;
  float bulbSec;
  int numShots;
  bool isRunning;

  unsigned long timeUntilNext();
  unsigned long timeUntilRelease();
  unsigned long timeUntilCompletion();
  void start(JsonDocument doc);
  void stop();
  void loop();

 private:
  float duration;
  unsigned long lastTime = 0;
  unsigned long startTime = 0;
  std::function<void()> sendStatus;

  void capture();
  void release();
};

#endif
