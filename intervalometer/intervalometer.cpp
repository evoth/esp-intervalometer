#include "intervalometer.h"

float intervalSec;
float bulbSec;
int numShots;
bool isRunning = false;
unsigned long lastTime;
// TODO: move this to camera.cpp?
bool isPressed = false;

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

void capture() {
  // TODO: quantize timing
  lastTime = millis();
  if (bulbMode) {
    pressShutter();
    isPressed = true;
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
  isPressed = false;
  sendStatus();
}

void startIntervalometer(DynamicJsonDocument doc) {
  getBulb();
  if (bulbMode) {
    bulbSec = doc["bulbSec"];
  } else {
    bulbSec = parseExpSetting();
  }

  intervalSec = doc["intervalSec"];
  numShots = 0;
  isRunning = true;

  capture();
}

void stopIntervalometer() {
  isRunning = false;
  release();
  if (statusCode == 200) {
    snprintf(statusMsg, sizeof(statusMsg), "Intervalometer stopped successfully.");
  }
}

// Run in main loop
void loopIntervalometer() {
  if (!isRunning) return;
  if (bulbMode && isPressed) {
    if (timeUntilRelease() > 0) return;
    release();
  }
  if (timeUntilNext() > 0) return;
  capture();
}