# Weather Clock LCD

ESP32-based weather station display for a 20x4 LCD. It shows the current date, time, indoor temperature, and local weather information retrieved from the [Open-Meteo API](https://open-meteo.com/) via WiFi. The display is updated periodically with separate refresh intervals for time, sensor data, and weather forecasts.

Example output:

```
2026-05-01 Thu 18:25
Room:20°C
☁ 21°C H:27°C L:13°C
W:9km/h R:53%
```

**Note**: 
* WiFi SSID, password, and location coordinates must be configured in `config.h`.
* The weather icons are displayed using custom 5x8 bitmaps that can be edited in `custom-bitmaps.h`.

## Components

### Hardware
* ESP32
* 20x4 LCD with I2C Interface
* BME280 Temperature, Humidity & Pressure Sensor

### Software
* IDE: Arduino IDE
* Arduino Library: [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C), [ArduinoJson 7](https://github.com/bblanchon/ArduinoJson), [Adafruit_BME280](https://github.com/adafruit/adafruit_bme280_library)

## Connection

| ESP32 | LCD I2C | BME280 |
|-------|-----|-----|
| VIN (5V) | VCC | VIN |
| GND | GND | GND |
| GPIO 21 (default SDA) | SDA | SDA |
| GPIO 22 (default SCL) | SCL | SCL |
