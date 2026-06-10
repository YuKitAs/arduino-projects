import logging
import time

import serial
from influxdb import InfluxDBClient

logging.basicConfig(filename='dust.log', format='%(asctime)s - %(levelname)s - %(message)s')

ser = serial.Serial('/dev/ttyACM0', 9600)
client = InfluxDBClient('localhost', 8086)
client.switch_database('dust')

while True:
    try:
        dust_value = float(ser.readline().strip())

        if dust_value >= 0:
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
        else:
            logging.warning('Ignored negative value: {}'.format(dust_value))
    except Exception as ex:
        logging.error(ex)
