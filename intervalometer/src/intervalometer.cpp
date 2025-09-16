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

// Time until completion in milliseconds (clamped at 0)
unsigned long Intervalometer::timeUntilCompletion() {
  unsigned long timeSinceStart = millis() - startTime;
  if (timeSinceStart >= duration * 1000)
    return 0;
  return (duration * 1000) - timeSinceStart;
}

void Intervalometer::action() {
  if (actionIndex >= 0 && actionIndex < sequence.size()) {
    String actionType = sequence[actionIndex]["actionType"];
    if (actionType == "CCAPI") {
      camera.executeAction(
          sequence[actionIndex]["name"], sequence[actionIndex]["httpMethod"],
          sequence[actionIndex]["endpointUrl"], sequence[actionIndex]["body"]);
    } else if (actionType == "IR_TRIGGER") {
      ir.trigger();
    }
  }
  actionIndex++;

  if (actionIndex >= sequence.size()) {
    numShots++;
    actionIndex = -1;
    cycleTime += intervalSec * 1000;
    if (millis() > cycleTime)
      cycleTime = millis();
    nextTime = cycleTime;
  } else {
    String timeMode = sequence[actionIndex]["timeMode"];
    float timeOffset = sequence[actionIndex]["time"];
    if (timeMode == "after previous") {
      nextTime = millis() + timeOffset * 1000;
    } else {
      nextTime = cycleTime + timeOffset * 1000;
    }
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

  nextTime = cycleTime = startTime = millis();
  intervalSec = doc["intervalSec"];
  duration = doc["duration"];
  numShots = 0;
  isRunning = true;

  action();
}

void Intervalometer::stop() {
  isRunning = false;
  startTime = 0;
  if (statusCode == 200) {
    snprintf(statusMsg, sizeof(statusMsg),
             "Intervalometer stopped successfully.");
  }
  sendStatus();
}

// Run in main loop
void Intervalometer::loop() {
  if (!isRunning)
    return;
  if (duration > 0 && timeUntilCompletion() <= 0) {
    stop();
    return;
  }
  if (timeUntilNext() > 0)
    return;
  action();
}