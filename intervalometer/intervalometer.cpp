#include "intervalometer.h"

int intervalSec;
int numShots;
bool isRunning = false;
unsigned long lastTime;

void capture() {
  lastTime = millis();
  triggerShutter();
  if (errorCode == 200) {
    numShots++;
  }
}

void startIntervalometer(AsyncWebServerRequest *request, DynamicJsonDocument doc) {
  intervalSec = doc["intervalSec"];
  numShots = 0;
  isRunning = true;

  capture();
  
  request->send(errorCode, "text/plain", errorMsg);
}

void stopIntervalometer(AsyncWebServerRequest *request) {
  isRunning = false;

  request->send(200, "text/plain", "Intervalometer stopped successfully.");
}

void getIntervalometerStatus(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(128);
  doc["numShots"] = numShots;
  doc["errorCode"] = errorCode;
  doc["errorMsg"] = errorMsg;
  String response;
  serializeJson(doc, response);
  request->send(200, "application/json", response);
}

void loopIntervalometer() {
  if (!isRunning) return;
  if ((millis() - lastTime) / 1000 < intervalSec) return;
  capture();
}