import logging
import statistics

import serial
from influxdb import InfluxDBClient

logging.basicConfig(filename='water.log', format='%(asctime)s - %(levelname)s - %(message)s')

ser = serial.Serial('/dev/ttyACM0', 9600)
client = InfluxDBClient('localhost', 8086)
client.switch_database('water')


def write_value(value):
    if value is not None:
        json_body = [{
            "measurement": "level",
            "tags": {
                "location": "home"
            },
            "fields": {
                "value": value
            }
        }]

        client.write_points(json_body)


while True:
    try:
        value = int(ser.readline().strip().decode('ascii'))
        if value <= 0:
            write_value(value)
    except Exception as ex:
        logging.error(ex)
