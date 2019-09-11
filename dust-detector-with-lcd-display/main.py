import serial

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    read_serial = float(ser.readline().strip())
    print(read_serial)