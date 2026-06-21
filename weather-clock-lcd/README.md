# Weather Clock LCD

Display current date, time, room temperature and location-based weather information on a 20x4 LCD using ESP32 and WiFi like:

```
2026-05-01 Thu 18:25
Room:20°C
☁ 21°C H:27°C L:13°C
W:9km/h R:53%
```

**Note**: The weather icons are displayed using custom 5x8 bitmaps that can be edited in `custom-bitmaps.h`.

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
