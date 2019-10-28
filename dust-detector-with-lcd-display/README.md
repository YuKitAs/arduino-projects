# Dust Detector with LCD Display

A device to detect the dust density and update the detected value on the LCD display in real-time. The data will be sent to InfluxDB and monitored with a Grafana dashboard running on RPi.

## Components
### Hardware
* Raspberry Pi 4 Model B
* Arduino UNO
* GP2Y1010AU0F Sharp Dust Sensor
* 16x2 LCD Display with I2C Interface
* 150 Ω Resitor
* 220 μF Capacitor

### Software
* OS: [Raspbian](https://www.raspberrypi.org/downloads/raspbian/)
* IDE: [Arduino IDE](https://www.arduino.cc/en/main/software)
* Arduino library: [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
* Database: [InfluxDB](https://docs.influxdata.com/influxdb/v1.7/)
* Database client: [InfluxDB-Python](https://github.com/influxdata/influxdb-python)
* Monitoring platform: [Grafana](https://grafana.com/docs/installation/debian/)
