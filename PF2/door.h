#include <Servo.h>

Servo doorServo;

int doorServoPin = 3;
int PIRPin = A5;

int pos = 180;
int speed = 1; // Degrees of each movement, i.e. speed of door

int sensMvmt;
int noiseThreshold = 100; // Threshold for recognizing PIR trigger

// setup
void setupDoor() { 
  doorServo.attach(doorServoPin);
  doorServo.write(pos);
}

// loop
void handleDoor() {
  delay(100);
  readSensor();
  
  if (sensMvmt >= noiseThreshold) {
    openDoor();
    delay(5000);
    closeDoor();
  }
}

void readSensor() {
  sensMvmt = analogRead(PIRPin);
  Serial.println(sensMvmt);
}

void openDoor() {
  for (pos; pos >= 0; pos -= 1) {
    doorServo.write(pos);
    delay(15);
  }
}

void closeDoor() {
  for (pos; pos <= 180; pos += 1) {
    doorServo.write(pos);
    delay(15);
  } 
}