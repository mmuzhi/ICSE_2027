import os

class CSVProcessor:
    def __init__(self):
        pass

    def read_csv(self, file_name):
        try:
            with open(file_name, 'r') as file:
                line = file.readline().strip()
                if not line:
                    return [], []
                title = line.split(',')
                
                data = []
                for line in file:
                    row = line.strip().split(',')
                    data.append(row)
                    
                return title, data
        except FileNotFoundError:
            return [], []
        except Exception as e:
            raise

    def write_csv(self, data, file_name):
        try:
            with open(file_name, 'w') as file:
                for row in data:
                    for i, item in enumerate(row):
                        file.write(item)
                        if i < len(row) - 1:
                            file.write(',')
                    file.write('\n')
            return 1
        except FileNotFoundError:
            return 0
        except Exception as e:
            raise

    def process_csv_data(self, N, save_file_name):
        # Extract the base name without extension
        if '.' in save_file_name:
            base = save_file_name.rsplit('.', 1)[0]
        else:
            base = save_file_name

        # Call read_csv
        title, data = self.read_csv(save_file_name)

        # Check if data is empty or if N is too large
        if not data or N >= len(data[0]):
            return 0

        column_data = []
        for row in data:
            if len(row) > N:
                column_data.append(row[N].upper())

        new_data = [title, column_data]

        return self.write_csv(new_data, base + '_process.csv')