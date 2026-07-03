class CSVProcessor:
    def __init__(self):
        pass

    def read_csv(self, file_name):
        try:
            with open(file_name, 'r') as file:
                content = file.read()
        except:
            return ([], [])
        
        lines = content.splitlines()
        if not lines:
            return ([], [])
        title = lines[0].split(',')
        data = [line.split(',') for line in lines[1:]]
        return (title, data)

    def write_csv(self, data, file_name):
        try:
            file = open(file_name, 'w')
        except:
            return 0
        
        try:
            for row in data:
                line = ','.join(row)
                file.write(line)
                file.write('\n')
        except:
            pass
        finally:
            file.close()
        
        return 1

    def process_csv_data(self, N, save_file_name):
        title, data = self.read_csv(save_file_name)
        if not data:
            return 0
        if N >= len(data[0]):
            return 0
        
        column_data = []
        for row in data:
            if N < len(row):
                upper_str = row[N].upper()
                column_data.append(upper_str)
        
        new_data = [title, column_data]
        
        if '.' in save_file_name:
            base = save_file_name.rsplit('.', 1)[0]
        else:
            base = save_file_name
        output_file = base + '_process.csv'
        
        return self.write_csv(new_data, output_file)