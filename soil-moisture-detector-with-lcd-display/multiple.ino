/*
* Display 4 soil moisture percentage values on 16x2 LCD with A0-A3 (A4 and A5 are used for SDA and SCL of the LCD)
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensor1 = 0; // A0
int sensor2 = 1; // A1
int sensor3 = 2; // A2
int sensor4 = 3; // A3

// change to the values measured in the air and water
const int AIR_VAL_1 = 447;
const int WATER_VAL_1 = 147;
const int AIR_VAL_2 = 446;
const int WATER_VAL_2 = 140;
const int AIR_VAL_3 = 618;
const int WATER_VAL_3 = 273;
const int AIR_VAL_4 = 436;
const int WATER_VAL_4 = 131;

void setup() {
  Serial.begin(9600);

  setupLcd();
}

void setupLcd() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();

  // read soil moisture values
  int input1 = analogRead(sensor1);
  int input2 = analogRead(sensor2);
  int input3 = analogRead(sensor3);
  int input4 = analogRead(sensor4);

  char output1[5];
  sprintf(output1, "1:%d%%", getPercentage(input1, AIR_VAL_1, WATER_VAL_1));
  lcd.setCursor(2, 0);
  lcd.print(output1);

  char output2[5];
  sprintf(output2, "2:%d%%", getPercentage(input2, AIR_VAL_2, WATER_VAL_2));
  lcd.setCursor(9, 0);
  lcd.print(output2);

  char output3[5];
  sprintf(output3, "3:%d%%", getPercentage(input3, AIR_VAL_3, WATER_VAL_3));
  lcd.setCursor(2, 1);
  lcd.print(output3);

  char output4[5];
  sprintf(output4, "4:%d%%", getPercentage(input4, AIR_VAL_4, WATER_VAL_4));
  lcd.setCursor(9, 1);
  lcd.print(output4);

  delay(5000);
}

int getPercentage(int value, int maxVal, int minVal) {
  int percentage = map(value, maxVal, minVal, 0, 100);
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;
  return percentage;
}
