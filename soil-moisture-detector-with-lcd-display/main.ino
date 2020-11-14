#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = 0;

const int airVal = 617; // change to the value measured in the air
const int waterVal = 270; // change to the value measured in the water
int intervals = (airVal - waterVal) / 3;

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
  int val = analogRead(sensorPin); // read soil moisture value
  Serial.println(val);

  lcd.setCursor(0, 1);
  if (val >= waterVal && val < (waterVal + intervals)) {
    lcd.print("    Very wet    ");
  } else if (val >= (waterVal + intervals) && val < (airVal - intervals)) {
    lcd.print("      Wet       ");
  } else if (val >= (airVal - intervals) && val <= airVal) {
    lcd.print("      Dry       ");
  }

  delay(1000);
}
