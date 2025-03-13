#ifndef ESP_INT_INTERVALOMETER_H
#define ESP_INT_INTERVALOMETER_H

#include <ArduinoJson.h>
#include <functional>
#include "camera.h"

class Intervalometer {
 public:
  Intervalometer(std::function<void()> sendStatus) : sendStatus(sendStatus) {
    deserializeJson(
        actions,
        "[{\"action\":\"Trigger "
        "shutter\",\"fields\":{},\"time\":0,\"timeMode\":\"from start\"}]");
  }

  Camera camera;
  float intervalSec = 0;
  int numShots = 0;
  bool isRunning = false;
  JsonDocument actions;

  unsigned long timeUntilNext();
  unsigned long timeUntilCompletion();
  void start(JsonDocument doc);
  void stop();
  void loop();

 private:
  float duration = 0;
  unsigned long nextTime = 0;
  unsigned long startTime = 0;
  std::function<void()> sendStatus;

  void capture();
};

#endif
