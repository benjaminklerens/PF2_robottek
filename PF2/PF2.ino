#include "fan.h"

void setup() {
  Serial.begin(9600);
  setupFan();
  Serial.println("program start");
}

void loop() {
  handleFan();
  delay(250);
}
