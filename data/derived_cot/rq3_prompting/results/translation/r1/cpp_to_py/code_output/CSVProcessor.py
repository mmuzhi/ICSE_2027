class CSVProcessor:
    def __init__(self):
        pass

    def read_csv(self, file_name):
        title = []
        data = []
        try:
            with open(file_name, 'r', newline='') as f:
                # Read header line
                line = f.readline()
                if line:
                    line = line.rstrip('\n')
                    # If line is empty after stripping newline, header is an empty row? Actually C++ would treat it as empty row.
                    # But header is supposed to be the first line; we handle consistently.
                    if line == '':
                        title = []
                    else:
                        title = line.split(',')
                # Read the rest lines
                for line in f:
                    line = line.rstrip('\n')
                    if line == '':
                        row = []
                    else:
                        row = line.split(',')
                    data.append(row)
        except FileNotFoundError:
            # Return empty title and data as C++ does when file cannot be opened
            pass
        return (title, data)

    def write_csv(self, data, file_name):
        try:
            with open(file_name, 'w', newline='') as f:
                for row in data:
                    f.write(','.join(row) + '\n')
        except:
            return 0
        return 1

    def process_csv_data(self, N, save_file_name):
        title, data = self.read_csv(save_file_name)
        # If file couldn't be read, data might be empty; same UB as C++ (IndexError)
        if N >= len(data[0]):
            return 0

        column_data = []
        for row in data:
            if N < len(row):
                column_data.append(row[N].upper())
        new_data = [title, column_data]

        # Build new file name: replace extension with '_process.csv'
        base = save_file_name.rsplit('.', 1)[0]
        new_file_name = base + '_process.csv'
        return self.write_csv(new_data, new_file_name)