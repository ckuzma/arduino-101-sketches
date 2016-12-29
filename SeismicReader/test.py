# import json
import serial
import sys


class SerialConnection:
    def __init__(self, port):
        self.connection = serial.Serial(port, 9600)

    def print_serial(self):
        while True:
            print(self.connection.readline())

if __name__ == '__main__':
    def usage():
        print('\n\tUsage:')
        print('\tpython ' + sys.argv[0] + ' ARG1')
        print('\n\tARG1 = port to connect to')

    if len(sys.argv) != 2:
        usage()
        exit()

    serial_connection = SerialConnection(sys.argv[1])
    serial_connection.print_serial()
