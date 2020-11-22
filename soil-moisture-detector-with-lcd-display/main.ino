#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = 0;

const int AIR_VAL = 617; // change to the value measured in the air
const int WATER_VAL = 270; // change to the value measured in the water

void setupLcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
}

void setup() {
  setupLcd();
  Serial.begin(9600);
}

void loop() {
  int input = analogRead(sensorPin); // read soil moisture value
  Serial.println(input);
  int percentage = map(input, AIR_VAL, WATER_VAL, 0, 100); // map to range [0, 100]
  Serial.println(percentage);

  lcd.setCursor(10, 0);
  lcd.print("    "); // clear value
  char output[4];
  sprintf(output, "%d%%", percentage);
  lcd.setCursor(10, 0);
  lcd.print(output);

  lcd.setCursor(0, 1);
  if (percentage >= 0 && percentage < 33) {
    lcd.print("      Dry       ");
  } else if (percentage >= 33 && percentage < 66) {
    lcd.print("      Wet       ");
  } else if (percentage >= 66 && percentage <= 100) {
    lcd.print("    Very wet    ");
  }

  delay(1000);
}
