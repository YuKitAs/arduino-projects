#include <Wire.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

Adafruit_BME280 bme;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define R_PIN 10  // D10
#define G_PIN 9  // D9
#define B_PIN 8  // D8

void temperatureToRGB(int temp, int &r, int &g, int &b) {
  temp = constrain(temp, 0, 40);

  if (temp <= 22) {
    // Blue -> Green
    r = 0;
    g = map(temp, 0, 22, 0, 255);
    b = map(temp, 0, 22, 255, 0);
  } else {
    // Green -> Red
    r = map(temp, 22, 40, 0, 255);
    g = map(temp, 22, 40, 255, 0);
    b = 0;
  }
}

void setup() {
  Serial.begin(9600);
  bme.begin(0x76);
  lcd.init();
  lcd.backlight();

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  delay(2000);

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
}
