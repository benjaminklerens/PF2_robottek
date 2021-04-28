#include "fan.h"
#include "door.h"
#include "alarm.h"

void setup() {
  Serial.begin(9600);
  Serial.println("smart home booting");
  setupFan();
  setupDoor();
  setupAlarm();
  Serial.println("smart home running");
}

void loop() {
  //runFan();
  handleFan();
  handleDoor();
  handleAlarm();
  delay(50);
}
