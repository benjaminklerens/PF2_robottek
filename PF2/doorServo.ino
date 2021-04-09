#include <Servo.h>

Servo doorServo;
int doorServoPin = 3;
int pos = 180;
int speed = 1; // Degrees of each movement, i.e. speed of door

void setup() {
  doorServo.attach(doorServoPin);

  doorServo.write(pos);
}

void loop() {
  //openDoor();
  //delay(2000);
  //closeDoor();
  //delay(2000);
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
