# Room Climate Monitor with RGB LED

This project extends the [Temperature and Humidity Detector with LCD](https://github.com/YuKitAs/arduino-projects/tree/master/temperature-and-humidity-detector-with-lcd) by replacing the DHT11 sensor with a more accurate BME280 sensor. It measures temperature, humidity, and air pressure, and uses an RGB LED indicator to visualize the temperature level.

## Components

### Hardware

* Arduino Nano
* BME280 Temperature, Humidity & Pressure Sensor
* 16x2 LCD with I2C Interface
* 4-Pin RGB LED Module

### Software

* IDE: Arduino IDE
* Arduino Library: [Adafruit_BME280](https://github.com/adafruit/adafruit_bme280_library), [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)

### Connection

| Arduino Nano | BME280 | LCD I2C | RGB LED |
|--------------|--------|---------|---------|
| VIN (5V)     | VIN    | VCC     |         |
| GND          | GND    | GND     | GND     |
| A4 (default SDA) | SDA  | SDA   |         |
| A5 (default SCL) | SCL  | SCL   |         |
| D10          |        |         | R       |
| D9           |        |         | G       |
| D8           |        |         | B       |
