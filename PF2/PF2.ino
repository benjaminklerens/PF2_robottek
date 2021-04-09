#include "fan.h"

void setup() {
  Serial.begin(9600);
  setupFan();
  Serial.println("program start");
}

void loop() {
  runFan();
  //handleFan();
  delay(250);
}
