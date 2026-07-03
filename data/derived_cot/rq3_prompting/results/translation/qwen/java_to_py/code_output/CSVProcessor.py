import os

class CSVProcessor:

    def read_csv(self, file_name, title, data):
        try:
            with open(file_name, 'r') as file:
                line = file.readline()
                if line is not None:
                    title.extend(line.strip().split(','))
                    for line_data in file:
                        data.append(line_data.strip().split(','))
        except FileNotFoundError:
            pass  # Java doesn't throw exceptions here, so we ignore

    def write_csv(self, title, data, file_name):
        try:
            with open(file_name, 'w', newline='') as file:
                file.write(','.join(title))
                file.write('\n')
                for row in data:
                    file.write(','.join(row))
                    file.write('\n')
            return 1
        except Exception:
            return 0

    def write_csv(self, data, file_name):
        try:
            with open(file_name, 'w', newline='') as file:
                for row in data:
                    file.write(','.join(row))
                    file.write('\n')
            return 1
        except Exception:
            return 0

    def process_csv_data(self, N, save_file_name):
        title = []
        data = []
        self.read_csv(save_file_name, title, data)
        column_data = []
        for row in data:
            if N < len(row):
                column_data.append(row[N].upper())
        new_data = [column_data]
        output_file = save_file_name.split('.')[0] + '_process.csv'
        return self.write_csv(title, new_data, output_file)