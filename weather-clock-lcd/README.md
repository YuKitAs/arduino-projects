# Weather Clock LCD

Display current date, time and location-based weather information on a 20x4 LCD using ESP32 and WiFi like:

```
2026-01-01 Thu 18:25
☁ 21°C W:9km/h
H:27°C L:13°C
Rain:53%
```

**Note**: The weather icons are displayed using custom 5x8 bitmaps that can be edited in `custom-bitmaps.h`.

## Components

### Hardware
* ESP32
* 20x4 LCD with I2C Interface

### Software
* IDE: Arduino IDE
* Arduino Library: [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C), [ArduinoJson 7](https://github.com/bblanchon/ArduinoJson)

## Connection

| ESP32 | LCD |
|-------|-----|
| VIN (5V) | VCC |
| GND | GND |
| GPIO 21 (default SDA) | SDA |
| GPIO 22 (default SCL) | SCL |
