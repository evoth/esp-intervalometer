#include <Arduino.h>
#include "status.h"
#include "server.h"
#include "intervalometer.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  initServer();
}

void loop()
{
  loopProcessRequest();
  loopIntervalometer();
}
