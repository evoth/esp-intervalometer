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

void Intervalometer::capture() {
  while (nextTime <= millis()) {
    nextTime += intervalSec * 1000;
  }

  camera.triggerShutter();

  if (statusCode == 200) {
    numShots++;
  }
  sendStatus();
}

void Intervalometer::start(JsonDocument doc) {
  actions = doc["actions"];

  startTime = millis();
  nextTime = startTime;
  intervalSec = doc["intervalSec"];
  duration = doc["duration"];
  numShots = 0;
  isRunning = true;

  capture();
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
  capture();
}