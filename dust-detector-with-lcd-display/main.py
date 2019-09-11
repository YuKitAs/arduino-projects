# Write your code here :-)
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
s = [0, 1]
while True:
    read_serial = float(ser.readline().strip())
    print("{0:.3f}".format(read_serial))