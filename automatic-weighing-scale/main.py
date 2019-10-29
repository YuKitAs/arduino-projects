import logging
import statistics
import time

import serial
from influxdb import InfluxDBClient

logging.basicConfig(filename='weight.log', format='%(asctime)s - %(levelname)s - %(message)s')

ser = serial.Serial('/dev/ttyACM0', 9600)
client = InfluxDBClient('localhost', 8086)
client.switch_database('weight')

num_read_values = 5
interval = 86400


def valid_values(values):
    return statistics.stdev(values) < 1


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


read_values = []

while True:
    try:
        if len(read_values) < num_read_values:
            value = int(ser.readline().strip().decode('ascii'))
            if value > 0:
                read_values.append(value)
            continue
        else:
            if valid_values(read_values):
                write_value(statistics.mean(read_values))
                time.sleep(interval)
            else:
                read_values = read_values[1:]
    except Exception as ex:
        logging.error(ex)
