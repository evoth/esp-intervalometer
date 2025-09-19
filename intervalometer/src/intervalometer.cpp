#include "intervalometer.h"
#include <Arduino.h>
#include "camera.h"
#include "status.h"

// Time until next shot in milliseconds (clamped at 0)
unsigned long Intervalometer::timeUntilNext() {
  unsigned long current = millis();
  if (current >= nextTime)
    return 0;
  return nextTime - current;
}

void Intervalometer::action() {
  bool endLoop = false;

  if (actionIndex >= 0 && actionIndex < sequence.size()) {
    String actionType = sequence[actionIndex]["actionType"];
    String actionName = sequence[actionIndex]["actionName"];
    if (actionType == "CCAPI") {
      camera.executeAction(sequence[actionIndex]["actionName"],
                           sequence[actionIndex]["httpMethod"],
                           sequence[actionIndex]["endpointUrl"],
                           sequence[actionIndex]["body"]);
    } else if (actionType == "IR_TRIGGER") {
      ir.trigger();
    } else if (actionType == "SERIAL") {
      String actionText;
      serializeJson(sequence[actionIndex], actionText);
      Serial.println(actionText);
      statusCode = 200;
      snprintf(statusMsg, sizeof(statusMsg),
               "Successfully sent '%s' action via serial.", actionName.c_str());
    } else if (actionType == "CONTROL") {
      if (actionName == "Loop") {
        loops.push_back(Loop(actionIndex + 1,
                             sequence[actionIndex]["body"]["duration"],
                             sequence[actionIndex]["body"]["repetitions"]));
        statusCode = 200;
        snprintf(statusMsg, sizeof(statusMsg), "Started loop ID=%d",
                 actionIndex + 1);
      } else if (actionName == "End loop") {
        endLoop = true;
      }
    }
  }
  actionIndex++;

  if (loops.empty()) {
    stop();
    return;
  }

  Loop& currentLoop = loops.back();

  if (actionIndex >= sequence.size() || endLoop) {
    currentLoop.completedReps++;

    if (isStopping) {
      stop();
      return;
    }

    if ((currentLoop.repetitions > 0 &&
         currentLoop.completedReps >= currentLoop.repetitions) ||
        (currentLoop.duration > 0 &&
         millis() - currentLoop.startTime >= currentLoop.duration * 1000)) {
      loops.pop_back();
      statusCode = 0;
      snprintf(statusMsg, sizeof(statusMsg), "Ending loop...", actionIndex + 1);
    } else {
      actionIndex = currentLoop.startIndex;
      currentLoop.cycleTime = millis();
      statusCode = 0;
      snprintf(statusMsg, sizeof(statusMsg), "Restarting loop...",
               actionIndex + 1);
    }
  }

  if (actionIndex >= sequence.size() || loops.empty()) {
    stop();
    return;
  }

  String timeMode = sequence[actionIndex]["timeMode"];
  float timeOffset = sequence[actionIndex]["time"];
  if (timeMode == "after previous") {
    nextTime = millis() + timeOffset * 1000;
  } else {
    nextTime = loops.back().cycleTime + timeOffset * 1000;
  }

  sendStatus();
}

void Intervalometer::start(JsonDocument doc) {
  actions = doc["actions"];
  sequence = doc["sequence"];
  if (sequence.size() == 0) {
    stop();
    return;
  }

  actionIndex = -1;
  loops.clear();
  loops.push_back(Loop(0, 0, 1));

  nextTime = millis();
  isRunning = true;
  isStopping = false;

  action();
}

void Intervalometer::stop() {
  isRunning = false;
  isStopping = false;
  statusCode = 200;
  snprintf(statusMsg, sizeof(statusMsg),
           "Intervalometer stopped successfully.");
  sendStatus();
}

void Intervalometer::stopAfterLast() {
  // Stop immediately if after last action or already stopping
  if (actionIndex == -1 || isStopping) {
    stop();
    return;
  }
  isStopping = true;
  statusCode = 0;
  snprintf(statusMsg, sizeof(statusMsg),
           "Stopping intervalometer after last action...");
  sendStatus();
}

// Run in main loop
void Intervalometer::loop() {
  if (!isRunning)
    return;
  if (timeUntilNext() > 0)
    return;
  action();
}