import time

import serial
from influxdb import InfluxDBClient

ser = serial.Serial('/dev/ttyACM0', 9600)
client = InfluxDBClient(host='localhost', port=8086)
client.switch_database('dust')

while True:
    dust_value = float(ser.readline().strip())
    json_body = [{
        "measurement": "dust_density",
        "tags": {
            "location": "home"
        },
        "fields": {
            "value": dust_value
        }
    }]

    client.write_points(json_body)

    time.sleep(30)
