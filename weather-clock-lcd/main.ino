#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_BME280.h>
#include "./custom-bitmaps.h"
#include "./config.h"

Adafruit_BME280 bme;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void clearLine(uint8_t row) {
  lcd.setCursor(0, row);
  lcd.print("                    ");  // 20 whitespaces
}

void displayTime() {
  struct tm t;
  if (!getLocalTime(&t)) return;

  char date[17], timebuf[17];
  strftime(date, sizeof(date), "%Y-%m-%d", &t);
  strftime(timebuf, sizeof(timebuf), "%H:%M", &t);

  const char* days[] = {
    "Sun", "Mon", "Tue", "Wed",
    "Thu", "Fri", "Sat"
  };

  lcd.setCursor(0, 0);
  lcd.print(date);
  lcd.setCursor(11, 0);
  lcd.print(days[t.tm_wday]);
  lcd.setCursor(15, 0);
  lcd.print(timebuf);
}

void displayTemp() {
  float tf = bme.readTemperature();
  int t = isnan(tf) ? 0 : (int)tf;

  clearLine(1);
  lcd.setCursor(0, 1);
  lcd.print("Room:");
  lcd.print(t);
  lcd.write(4);
}

const int8_t weatherIcon(int code) {
  // Open-Meteo codes
  if (code == 0) return 0;   // sunny
  if (code <= 3) return 1;   // cloudy
  if (code <= 67) return 2;  // rainy
  if (code <= 86) return 3;  // snowy
  return -1;                 // unknown
}

void displayWeather() {
  HTTPClient http;

  String url =
    "https://api.open-meteo.com/v1/forecast?latitude=" + String(LAT) + "&longitude=" + String(LONG) + "&current=temperature_2m,weather_code,wind_speed_10m&daily=temperature_2m_max,temperature_2m_min,precipitation_probability_max";

  http.begin(url);
  http.setTimeout(5000);

  int res = http.GET();

  if (res != HTTP_CODE_OK) {
    http.end();
    return;
  }

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, http.getString());

  if (err) {
    http.end();
    return;
  }

  float temp = doc["current"]["temperature_2m"];
  int weatherCode = doc["current"]["weather_code"];
  float windSpeed = doc["current"]["wind_speed_10m"];
  float maxTemp = doc["daily"]["temperature_2m_max"][0];
  float minTemp = doc["daily"]["temperature_2m_min"][0];
  int rainChance = doc["daily"]["precipitation_probability_max"][0];

  clearLine(2);
  lcd.setCursor(0, 2);

  int8_t icon = weatherIcon(weatherCode);

  if (icon >= 0)
    lcd.write((uint8_t)icon);
  else
    lcd.print('?');

  lcd.setCursor(2, 2);
  lcd.print((int)temp);
  lcd.write(4);

  lcd.print(" H:");
  lcd.print((int)maxTemp);
  lcd.write(4);

  lcd.print(" L:");
  lcd.print((int)minTemp);
  lcd.write(4);

  clearLine(3);
  lcd.setCursor(0, 3);
  lcd.print("W:");
  lcd.print((int)windSpeed);
  lcd.print("km/h");

  lcd.print(" R:");
  lcd.print(rainChance);
  lcd.print("%");

  http.end();
}


void setup() {
  Wire.begin(21, 22);

  bme.begin(0x76);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  configTime(0, 0, "de.pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
  tzset();

  struct tm t;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Syncing...");

  while (!getLocalTime(&t)) {
    delay(500);
  }

  lcd.createChar(0, sunny);
  lcd.createChar(1, cloudy);
  lcd.createChar(2, rainy);
  lcd.createChar(3, snowy);
  lcd.createChar(4, degC);

  lcd.clear();
  displayTime();
  displayTemp();
  displayWeather();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    delay(5000);
  }

  static unsigned long lastTick = 0;
  static int tickCount = 0;

  if (millis() - lastTick >= 10000) {  // refresh time every 10s
    lastTick = millis();
    displayTime();

    tickCount++;

    if (tickCount % 6 == 0) {  // refresh room temperature every 60s (6 * 10s)
      displayTemp();
    }

    if (tickCount >= 90) {  // refresh weather every 15min (90 * 10s)
      displayWeather();
      tickCount = 0;
    }
  }
}