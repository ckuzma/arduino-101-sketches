import json
import os
import serial
import sys

class SerialConnection:
    def __init__(self, port):
        self.connection = serial.Serial(port, 250000)
        self.grapher = CurieGrapher()

    def debug_print_json(self, data, debug=False):
        if debug is True:
            print(json.dumps(data, indent=2))

    def read_serial(self):
        ## Get line from Serial
        data_point = self.connection.readline().decode('utf8')

        cont = False
        while cont is False:
        ## Try to decode a JSON from the string
            try:
                data_point = json.loads(data_point)
                cont = True
            except:
                print('ERROR: Unable to decode JSON from Serial')
                print(data_point)
        return data_point

    def get_curie_loop(self):
        ## Connect to Serial
        try:
            serial_connection = SerialConnection(sys.argv[1])
        except serial.serialutil.SerialException as e:
            print('ERROR:')
            print(e)

        ## Get data off of serial, loops
        while True:
            data_point = self.read_serial()
            self.debug_print_json(data_point)
            if data_point is not None:
                self.grapher.graph_live_data(data_point)

class CurieGrapher:
    def build_bar_graph(self, label, value, minimum, maximum):
        return label + '  ' + self.draw_bar(value, minimum, maximum)

    def graph_live_data(self, input_data):
        try:
            output_string = self.build_bar_graph('ax (' + input_data['ax'] + ')', input_data['ax'], -20000, 20000) + '\n'
            output_string += self.build_bar_graph('ay', input_data['ay'], -20000, 20000) + '\n'
            output_string += self.build_bar_graph('az', input_data['az'], -20000, 20000) + '\n'
            output_string += self.build_bar_graph('gx', input_data['gx'], -20000, 20000) + '\n'
            output_string += self.build_bar_graph('gy', input_data['gy'], -20000, 20000) + '\n'
            output_string += self.build_bar_graph('gz', input_data['gz'], -20000, 20000)
            os.system('cls')
            print(output_string)
        except:
            pass


    def draw_bar(self, bar_val, min_limit, max_limit, points=80):
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

    serial_connection = SerialConnection(sys.argv[1])
    serial_connection.get_curie_loop()
