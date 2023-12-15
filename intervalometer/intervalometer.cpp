#include "intervalometer.h"

int intervalSec;
int numShots;
bool isRunning = false;
unsigned long lastTime;

unsigned long timeUntilNext() {
  unsigned long timeSinceLast = millis() - lastTime;
  if (timeSinceLast >= intervalSec * 1000) return 0;
  return (intervalSec * 1000) - timeSinceLast;
}

void capture() {
  // TODO: quantize timing
  lastTime = millis();
  triggerShutter();
  if (statusCode == 200) {
    numShots++;
  }
  sendStatus();
}

void startIntervalometer(DynamicJsonDocument doc) {
  intervalSec = doc["intervalSec"];
  numShots = 0;
  isRunning = true;

  capture();
}

void stopIntervalometer() {
  isRunning = false;

  statusCode = 200;
  snprintf(statusMsg, sizeof(statusMsg), "Intervalometer stopped successfully.");
}

void loopIntervalometer() {
  if (!isRunning) return;
  if (timeUntilNext() > 0) return;
  capture();
}