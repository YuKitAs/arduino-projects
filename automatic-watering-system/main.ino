#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = 0; // A0
int pumpPin = 8; // D8

int percentage = 0;
int threshold = 10; // threshold to trigger pump
int duration = 1000; // pump duration in milliseconds

const int AIR_VAL = 628;
const int WATER_VAL = 270;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  initLcd();
  displayVal();

  if (percentage < threshold) {
    // pump for [duration] ms
    digitalWrite(pumpPin, HIGH);
    delay(duration);
    digitalWrite(pumpPin, LOW);
  } else {
    digitalWrite(pumpPin, LOW);
  }

  delay(5000);
}


void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
}

void displayVal() {
  int input = analogRead(sensorPin);
  Serial.println(input);
  percentage = map(input, AIR_VAL, WATER_VAL, 0, 100);
  Serial.println(percentage);

  lcd.setCursor(10,0);
  lcd.print("    ");
  char output[4];
  sprintf(output, "%d%%", percentage);
  lcd.setCursor(10,0);
  lcd.print(output);

  lcd.setCursor(0,1);
  if (percentage >= 0 && percentage < 33) {
    lcd.print("      Dry       ");
  } else if (percentage >= 33 && percentage < 66) {
    lcd.print("      Wet       ");
  } else if (percentage >= 66 && percentage <= 100) {
    lcd.print("    Very wet    ");
  }
}
