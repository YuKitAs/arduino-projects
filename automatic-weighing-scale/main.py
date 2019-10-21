import logging
import time

import serial
from influxdb import InfluxDBClient

logging.basicConfig(filename='weight.log', format='%(asctime)s - %(levelname)s - %(message)s')

ser = serial.Serial('/dev/ttyACM0', 9600)
client = InfluxDBClient('localhost', 8086)
client.switch_database('weight')

num_stable_values = 10


def has_valid_value(values: list):
    return values.count(values[0]) == num_stable_values


def write_value(value):
    if value:
        json_body = [{
            "measurement": "weight",
            "tags": {
                "location": "home"
            },
            "fields": {
                "value": value
            }
        }]

        client.write_points(json_body)


result_values = []

while True:
    try:
        if len(result_values) < num_stable_values:
            value = int(ser.readline().strip().decode('ascii'))
            if int(value) > 0:
                result_values.append(int(value))
            continue
        else:
            if has_valid_value(result_values):
                write_value(result_values[0])
                time.sleep(86400)
            else:
                result_values = result_values[1:]
    except Exception as ex:
        logging.error(ex)
