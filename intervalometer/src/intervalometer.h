#ifndef ESP_INT_INTERVALOMETER_H
#define ESP_INT_INTERVALOMETER_H

#include <ArduinoJson.h>
#include <functional>
#include "camera.h"
#include "ir.h"

class Intervalometer {
 public:
  Intervalometer(std::function<void()> sendStatus)
      : ir(13), sendStatus(sendStatus) {
    deserializeJson(
        actions,
        "[{\"action\":\"Trigger "
        "shutter\",\"fields\":{},\"time\":0,\"timeMode\":\"from start\"}]");
    deserializeJson(sequence, "[]");
  }

  CCAPI camera;
  IR ir;
  float intervalSec = 0;
  int numShots = 0;
  bool isRunning = false;
  JsonDocument actions;
  JsonDocument sequence;
  int actionIndex = 0;

  unsigned long timeUntilNext();
  unsigned long timeUntilCompletion();
  void start(JsonDocument doc);
  void stop();
  void loop();

 private:
  float duration = 0;
  unsigned long nextTime = 0;
  unsigned long startTime = 0;
  unsigned long cycleTime = 0;
  std::function<void()> sendStatus;

  void action();
};

#endif
