#include <Arduino.h>
#include "intervalometer.h"
#include "server.h"
#include "status.h"

ESPServer server;

void setup() {
  Serial.begin(115200);
  Serial.println();
  server.initServer();
}

void loop() {
  server.loop();
}
