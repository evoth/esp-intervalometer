// Source: https://r6500.blogspot.com/2014/11/canon-ir-trigger.html

#include "ir.h"
#include "status.h"

void burst(int ledPin) {
  for (int i = 0; i < 16; i++) {
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(12);
    digitalWrite(ledPin, LOW);
    delayMicroseconds(12);
  }
}

void IR::trigger() {
  burst(ledPin);
  delayMicroseconds(6635);
  burst(ledPin);

  statusCode = 200;
  snprintf(statusMsg, sizeof(statusMsg), "Successfully emitted IR burst.");
}