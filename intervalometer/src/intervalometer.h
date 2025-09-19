#ifndef ESP_INT_INTERVALOMETER_H
#define ESP_INT_INTERVALOMETER_H

#include <ArduinoJson.h>
#include <functional>
#include <vector>
#include "camera.h"
#include "ir.h"

struct Loop {
  int startIndex;
  unsigned long startTime;
  unsigned long cycleTime;
  float duration;
  int repetitions;
  int completedReps;

  Loop(int startIndex, float duration, int repetitions)
      : startIndex(startIndex),
        startTime(millis()),
        cycleTime(millis()),
        duration(duration),
        repetitions(repetitions),
        completedReps(0) {}
};

class Intervalometer {
 public:
  Intervalometer(std::function<void()> sendStatus)
      : ir(13), loops(), sendStatus(sendStatus) {
    deserializeJson(
        actions,
        "[{\"action\":\"Trigger "
        "shutter\",\"fields\":{},\"time\":0,\"timeMode\":\"from start\"}]");
    deserializeJson(sequence, "[]");
  }

  CCAPI camera;
  IR ir;
  bool isRunning = false;
  bool isStopping = false;
  JsonDocument actions;
  JsonDocument sequence;
  int actionIndex = 0;
  std::vector<Loop> loops;

  unsigned long timeUntilNext();
  void start(JsonDocument doc);
  void stop();
  void stopAfterLast();
  void loop();

 private:
  unsigned long nextTime = 0;
  std::function<void()> sendStatus;

  void action();
};

#endif
