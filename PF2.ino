
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

#define MOTOR_PIN 12
void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.println("program start");
}

void loop() {
  delay(250);
  Serial.println(readTemp());
  if(readTemp() > 20.00){
    digitalWrite(MOTOR_PIN,1);
  } else {
    digitalWrite(MOTOR_PIN,0);
  }

}

float readTemp() {
 Vo = analogRead(ThermistorPin);
 R2 = R1 * (1023.0 / (float)Vo - 1.0);
 logR2 = log(R2);
 T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
 Tc = T - 273.15;
  

  return Tc;

}
