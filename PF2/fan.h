#define MOTOR_PIN 13

int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 0.001125308852122, c2 = 0.000234711863267, c3 = 0.000000085663516;

boolean fanRunning = false;

void setupFan() {
  pinMode(MOTOR_PIN, OUTPUT);
}

float readTemp() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  return Tc;

}

void runFan() {
  digitalWrite(MOTOR_PIN, 1);
  fanRunning = true;
}

void stopFan() {
  digitalWrite(MOTOR_PIN, 0);
  fanRunning = false;
}

void handleFan() {
  if (readTemp() > 30.00 && !fanRunning) {
    runFan();
  } else if (readTemp() < 30.00 && fanRunning){
    stopFan();
  }
}
