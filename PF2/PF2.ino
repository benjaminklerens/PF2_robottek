#include "fan.h"
#include "door.h"
#include "alarm.h"

void printStates() {
  Serial.print("Is the fan running: ");
  Serial.println(fanRunning);

  Serial.print("Is the door open: ");
  Serial.println(isOpen);

  Serial.print("Is the alarm active: ");
  Serial.println(alarmActive);
}

void setup() {
  Serial.begin(9600);
  Serial.println("smart home booting");
  setupFan();
  setupDoor();
  setupAlarm();
  Serial.println("smart home running");
}

void loop() {
  printStates();
  handleFan();
  handleDoor();
  handleAlarm();
  delay(50);
}
