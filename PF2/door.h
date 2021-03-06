#include <Servo.h>

Servo doorServo;

int doorServoPin = 5;
int PIRPin = A3;

boolean isOpen = false;
unsigned long previousTime;


int sensMvmt;
int noiseThreshold = 100; // Threshold for recognizing PIR trigger

void readSensor() {
  sensMvmt = analogRead(PIRPin);
}

void openDoor() {
  doorServo.write(0);
  isOpen = true;
}

void closeDoor() {
  doorServo.write(180);
  isOpen = false;
}

// setup
void setupDoor() {
  doorServo.attach(doorServoPin);
  previousTime = millis();
  closeDoor();
}

// loop
void handleDoor() {
  readSensor();

  if (sensMvmt >= noiseThreshold && isOpen == false) {
    openDoor();
    previousTime = millis();
  } else if ((millis() - previousTime) >= 5000) {
    closeDoor();
  }
}
