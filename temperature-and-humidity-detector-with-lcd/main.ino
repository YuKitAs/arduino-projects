#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 // D2 connected to the DHT sensor
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  delay(2000);

  // Read relative humidity
  int h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(3,1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("\xDF""C");
}
