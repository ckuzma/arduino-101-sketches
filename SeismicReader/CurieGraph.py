import json
import os
import serial
import sys

MAX = {
    'ax': 0,
    'ay': 0,
    'az': 0,
    'gx': 0,
    'gy': 0,
    'gz': 0
}
MIN = {
    'ax': 0,
    'ay': 0,
    'az': 0,
    'gx': 0,
    'gy': 0,
    'gz': 0
}

class CurieGrapher:
    def calculate_min_max(self, input_data):
        for key,value in input_data.items():
            if value > MAX[key]:
                MAX[key] = value
            if value < MIN[key]:
                MIN[key] = value

    def build_bar_graph(self, label, value, minimum, maximum):
        return label + '  ' + self.draw_bar(value, minimum, maximum)

    def graph_live_data(self, input_data):
        self.calculate_min_max(input_data)
        output_string = self.build_bar_graph('ax (' + str(input_data['ax']) + ')\t', input_data['ax'], -25000, 25000) + '\n'
        output_string += self.build_bar_graph('ay (' + str(input_data['ay']) + ')\t', input_data['ay'], -25000, 25000) + '\n'
        output_string += self.build_bar_graph('az (' + str(input_data['az']) + ')\t', input_data['az'], -25000, 25000) + '\n'
        output_string += self.build_bar_graph('gx (' + str(input_data['gx']) + ')\t', input_data['gx'], -35000, 35000) + '\n'
        output_string += self.build_bar_graph('gy (' + str(input_data['gy']) + ')\t', input_data['gy'], -35000, 35000) + '\n'
        output_string += self.build_bar_graph('gz (' + str(input_data['gz']) + ')\t', input_data['gz'], -35000, 35000) + '\n\n'
        output_string += 'ax\tMAX = ' + str(MAX['ax']) + '\tMIN = ' + str(MIN['ax']) + '\n'
        output_string += 'ay\tMAX = ' + str(MAX['ay']) + '\tMIN = ' + str(MIN['ay']) + '\n'
        output_string += 'az\tMAX = ' + str(MAX['az']) + '\tMIN = ' + str(MIN['az']) + '\n'
        output_string += 'gx\tMAX = ' + str(MAX['gx']) + '\tMIN = ' + str(MIN['gx']) + '\n'
        output_string += 'gy\tMAX = ' + str(MAX['gy']) + '\tMIN = ' + str(MIN['gy']) + '\n'
        output_string += 'gz\tMAX = ' + str(MAX['gz']) + '\tMIN = ' + str(MIN['gz'])
        if sys.platform == 'win32':
            os.system('cls')
        else:
            os.system('clear')
        print(output_string)


    def draw_bar(self, bar_val, min_limit, max_limit, points=40):
        """
        bar_val     = value to plot on the line
        min_limit   = minimum value point on the line
        max_limit   = maximum value point on the line
        points      = gradient of the line; higher number = finer grained

        Returns a string that looks like this:
            min|---------X----|max
        """
        label_min = str(min_limit)
        label_max = str(max_limit)
        min_limit = abs(min_limit)
        max_limit += min_limit
        location = int((bar_val + min_limit) / max_limit * points)
        bar_string = label_min + '|'
        x = 0
        while x < points:
            if x != location:
                bar_string += '-'
            else:
                bar_string += 'X'
            x+=1
        bar_string += '|' + label_max
        return bar_string




if __name__ == '__main__':
    def usage():
        print('\n\tUsage:')
        print('\tpython ' + sys.argv[0] + ' ARG1')
        print('\n\tARG1 = port to connect to')

    if len(sys.argv) != 2:
        usage()
        exit()

    ## Instantiate our graphing class
    curie_grapher = CurieGrapher()

    ## Initialize the Serial connection
    ser = serial.Serial(sys.argv[1], 9600)

    ## Begin the loop
    while True:
        raw_serial_data = ser.readline()
        # print(raw_serial_data) # For debugging
        sensor_data = json.loads(raw_serial_data)
        curie_grapher.graph_live_data(sensor_data)
