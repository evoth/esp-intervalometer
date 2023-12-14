#include "intervalometer.h"

int intervalSec;
int numShots;
bool isRunning = false;
unsigned long lastTime;

void capture() {
  // TODO: quantize timing
  lastTime = millis();
  triggerShutter();
  if (statusCode == 200) {
    numShots++;
  }
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
  if ((millis() - lastTime) / 1000 < intervalSec) return;
  capture();
}