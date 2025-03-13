#include "intervalometer.h"
#include <Arduino.h>
#include "camera.h"
#include "status.h"

// Time until next shot in milliseconds (clamped at 0)
unsigned long Intervalometer::timeUntilNext() {
  unsigned long timeSinceLast = millis() - lastTime;
  if (timeSinceLast >= intervalSec * 1000)
    return 0;
  return (intervalSec * 1000) - timeSinceLast;
}

// Time until completion in milliseconds (clamped at 0)
unsigned long Intervalometer::timeUntilCompletion() {
  unsigned long timeSinceStart = millis() - startTime;
  if (timeSinceStart >= duration * 1000)
    return 0;
  return (duration * 1000) - timeSinceStart;
}

void Intervalometer::capture() {
  // If we're within 2 intervals of lastTime, quantize the time
  unsigned long elapsed = millis() - lastTime;
  unsigned long interval = intervalSec * 1000;
  if (elapsed < 2 * interval) {
    lastTime += elapsed - elapsed % interval;
  } else {
    lastTime += elapsed;
  }

  camera.triggerShutter();

  if (statusCode == 200) {
    numShots++;
  }
  sendStatus();
}

void Intervalometer::start(JsonDocument doc) {
  lastTime = millis();
  startTime = millis();
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