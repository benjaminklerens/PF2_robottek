#include "fan.h"
#include "door.h"
#include "alarm.h"

boolean lastFanRunning;
boolean lastIsOpen;
boolean lastAlarmActive;

void printStates() {
  if (lastFanRunning != fanRunning) {
    Serial.print("Is the fan running: ");
    Serial.println(fanRunning);
  }

  if (lastIsOpen != isOpen) {
    Serial.print("Is the door open: ");
    Serial.println(isOpen);
  }

  if (lastAlarmActive != alarmActive) {
    Serial.print("Is the alarm active: ");
    Serial.println(alarmActive);
  }

  lastFanRunning = fanRunning;
  lastIsOpen = isOpen;
  lastAlarmActive = alarmActive;
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
