#ifndef ESP_INT_IR_H
#define ESP_INT_IR_H

#include "Arduino.h"

class IR {
 public:
  IR(int ledPin) : ledPin(ledPin) {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  }

  void trigger();

 private:
  int ledPin;
};

#endif
