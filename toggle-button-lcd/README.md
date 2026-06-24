# Toggle Button LCD

Demonstrate how a push button can be used as a toggle switch to control the backlight of an I2C LCD display.

## Components

* ESP32
* 20x4 LCD with I2C Interface
* Push button (4 pins)

## Connections

| ESP32 | LCD I2C | Button |
|-------|-----|-----|
| VIN (5V) | VCC | |
| GND | GND | GND |
| GPIO 18 | | Button Input |
| GPIO 21 (default SDA) | SDA | |
| GPIO 22 (default SCL) | SCL | |
