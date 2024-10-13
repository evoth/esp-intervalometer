#include "intervalometer.h"
#include "camera.h"
#include "server.h"
#include "status.h"
#include <Arduino.h>

float intervalSec;
float bulbSec;
float duration;
int numShots;
bool isRunning = false;
unsigned long lastTime = 0;
unsigned long startTime = 0;
// TODO: move this to camera.cpp?

// Time until next shot in milliseconds (clamped at 0)
unsigned long timeUntilNext() {
  unsigned long timeSinceLast = millis() - lastTime;
  if (timeSinceLast >= intervalSec * 1000) return 0;
  return (intervalSec * 1000) - timeSinceLast;
}

// Time until bulb shutter release in milliseconds (clamped at 0)
unsigned long timeUntilRelease() {
  unsigned long timeSinceLast = millis() - lastTime;
  if (timeSinceLast >= bulbSec * 1000) return 0;
  return (bulbSec * 1000) - timeSinceLast;
}

// Time until completion in milliseconds (clamped at 0)
unsigned long timeUntilCompletion() {
  unsigned long timeSinceStart = millis() - startTime;
  if (timeSinceStart >= duration * 1000) return 0;
  return (duration * 1000) - timeSinceStart;
}

void capture() {
  // If we're within 2 intervals of lastTime, quantize the time
  unsigned long elapsed = millis() - lastTime;
  unsigned long interval = intervalSec * 1000;
  if (elapsed < 2 * interval) {
    lastTime += elapsed - elapsed % interval;
  } else {
    lastTime += elapsed;
  }

  if (bulbMode) {
    pressShutter();
  } else {
    triggerShutter();
  }

  if (statusCode == 200) {
    numShots++;
  }
  sendStatus();
}

void release() {
  releaseShutter();
  sendStatus();
}

void startIntervalometer(JsonDocument doc) {
  getBulb();
  if (bulbMode) {
    bulbSec = doc["bulbSec"];
  } else {
    bulbSec = parseExpSetting();
  }

  lastTime = millis();
  startTime = millis();
  intervalSec = doc["intervalSec"];
  duration = doc["duration"];
  numShots = 0;
  isRunning = true;

  capture();
}

void stopIntervalometer() {
  isRunning = false;
  startTime = 0;
  release();
  if (statusCode == 200) {
    snprintf(statusMsg, sizeof(statusMsg), "Intervalometer stopped successfully.");
  }
}

// Run in main loop
void loopIntervalometer() {
  if (!isRunning) return;
  if (duration > 0 && timeUntilCompletion() <= 0) {
    stopIntervalometer();
    return;
  }
  if (bulbMode && shutterIsPressed) {
    if (timeUntilRelease() > 0) return;
    release();
  }
  if (timeUntilNext() > 0) return;
  capture();
}