# Automatic Weighing Scale

A scale to weigh a small animal lighter than 5kg. The weight value will be automatically recorded after the animal sits on the scale for 10 seconds, and at most once every 24 hours. The data will be sent to InfluxDB and monitored with a Grafana dashboard running on RPi.

## Components
### Hardware
* Raspberry Pi 4 Model B
* Arduino UNO
* HX711 24-bit AD Module
* 5kg Aluminum Alloy Weight Sensor (Load Cell)

### Software
* OS: Raspbian
* IDE: Arduino IDE
* Arduino library: [HX711_ADC](https://github.com/olkal/HX711_ADC)
* Database: InfluxDB
* Database client: InfluxDB-Python
* Monitoring platform: Grafana

## Connection
![](https://github.com/YuKitAs/arduino-projects/blob/master/automatic-weighing-scale/connection.png)
