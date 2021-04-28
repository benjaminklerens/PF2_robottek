#include <LiquidCrystal.h>
#include <RTClib.h>
#include <EEPROM.h>

#define SW 2
#define BUZZER_PIN 13
#define CLK 3
#define DT 4

RTC_DS1307 rtc;

int buttonState, lastButtonState;
int stateCLK, lastStateCLK;

int alarmHour_addr = 0;
int alarmMinute_addr = 1;
int sens = 5;
int alarmDuration = 5;
int alarmHour, alarmMinute;

boolean alarmActive = true;

boolean alarmChanged = false;

DateTime now;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);

// Print the current time to the LCD
void printLCDTime() {
  lcd.setCursor(0, 1);
  if (now.hour() < 10) {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
}

// Print the current alarm timer to the LCD
void printLCDAlarm() {
  lcd.setCursor(0, 1);
  if (alarmHour < 10) {
    lcd.print("0");
  }
  lcd.print(alarmHour, DEC);
  lcd.print(":");
  if (alarmMinute < 10) {
    lcd.print("0");
  }
  lcd.print(alarmMinute, DEC);
}

void printLCD() {
  if (!alarmActive) {
    printLCDAlarm();
  } else {
    printLCDTime();
  }
}

// Decrease alarm timer by the value of 'sens'
void decreaseAlarm() {
  if (alarmMinute - sens < 0) {
    if (alarmHour > 0) {
      alarmHour--;
      alarmMinute = 60 - sens;
    }
  } else {
    alarmMinute = alarmMinute - sens;
  }
}

// Increase alarm timer by the value of 'sens'
void increaseAlarm() {
  if  (alarmMinute + sens >= 60) {
    if (alarmHour < 23) {
      alarmHour++;
      alarmMinute = 0;
    }
  } else {
    alarmMinute = alarmMinute + sens;
  }
}

void rotate() {
  if (!alarmActive) {
    stateCLK = digitalRead(CLK);
    // If the previous and the current state of CLK are different, that means a Pulse has occured
    if (stateCLK != lastStateCLK && stateCLK == 1) {
      // If DT state is different to CLK state, that means the encoder is rotating clockwise
      if (digitalRead(DT) != stateCLK) {
        decreaseAlarm();
      } else {
        increaseAlarm();
      }
      alarmChanged = true;
    }
    lastStateCLK = stateCLK; // Updates the previous state of the CLK with the current state
  }
}

void saveAlarm() {
  if (EEPROM.read(alarmHour_addr) != alarmHour) {
    EEPROM.write(alarmHour_addr, alarmHour);
  }
  if (EEPROM.read(alarmMinute_addr) != alarmMinute) {
    EEPROM.write(alarmMinute_addr, alarmMinute);
  }
  Serial.println("wrote alarm to eeprom!");
}

void runAlarm() {
  delay(500);
  digitalWrite(BUZZER_PIN, 1);
  delay(500);
  digitalWrite(BUZZER_PIN, 0);
}

void setupAlarm() {
  if (!rtc.begin()) {
    Serial.println("Could not find RTC!");
  }


  if (!rtc.isrunning()) {
    Serial.println("RTC not running, setting time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  alarmHour = EEPROM.read(alarmHour_addr);
  alarmMinute = EEPROM.read(alarmMinute_addr);

  // Uncomment to reset clock
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Uncomment to reset EEPROM
  // EEPROM.write(alarmHour_addr, 8);
  // EEPROM.write(alarmMinute_addr, 0);

  // Using the internal pullup resistors for the rotary encoder
  pinMode(SW, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lastStateCLK = digitalRead(CLK);
  lastButtonState = digitalRead(SW);

  // Attaching interrupt to CLK pin of rotary encoder
  // (This is needed to make sure each change is registered)
  attachInterrupt(digitalPinToInterrupt(CLK), rotate, CHANGE);
  lcd.print("Current time:");
}

void handleAlarm() {

  // Fetch new time info from RTC
  now = rtc.now();

  // Check if alarm is active, run alarm if time is equal to the time of the alarm
  if (alarmActive == true) {
    if (alarmHour == now.hour() && alarmHour == now.minute() && now.second() <= alarmDuration) {
      runAlarm();
    }
  }

  // Change mode when button is pressed
  buttonState = digitalRead(SW);
  if (buttonState != lastButtonState && buttonState == 0) {
    alarmActive = !alarmActive;
    lcd.clear();
    if (alarmActive) {
      saveAlarm();
      lcd.print("Current time:");
    }
    else {
      lcd.print("Alarm time:");
    }
  }
  printLCD();
  lastButtonState = buttonState;
}
