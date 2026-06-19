#include <Wire.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

Adafruit_BME280 bme;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define R_PIN 10  // D10
#define G_PIN 9  // D9
#define B_PIN 8  // D8

void temperatureToRGB(int temp, int &r, int &g, int &b) {
  if (temp <= 15) {
    // blue
    r = 0;
    g = 0;
    b = 255;
  } else if (temp >= 30) {
    // red
    r = 255;
    g = 0;
    b = 0;
  } else {
    // 15-22°C: blue -> green; 22-30°C green -> red
    if (temp <= 22) {
      r = 0;
      g = map(temp * 10, 150, 220, 0, 255);
      b = map(temp * 10, 150, 220, 255, 0);
    } else {
      r = map(temp * 10, 220, 300, 0, 255);
      g = map(temp * 10, 220, 300, 255, 0);
      b = 0;
    }
  }
}

void setup() {
  Wire.begin();

  bme.begin(0x76);
  lcd.init();
  lcd.backlight();

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  delay(1000);
}

void loop() {
  // Read temperature as Celsius
  float tf = bme.readTemperature();
  int t = isnan(tf) ? 0 : (int)tf;

  // Read relative humidity
  float hf = bme.readHumidity();
  int h = isnan(hf) ? 0 : (int)hf;

  // Read air pressure and convert to hPa
  float pf = bme.readPressure();
  int p = isnan(pf) ? 0 : (int)(pf / 100.0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("\xDF"
            "C");

  lcd.print(" H:");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(p);
  lcd.print("hPa");

  int r, g, b;
  temperatureToRGB(t, r, g, b);
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);

  delay(60000);
}
