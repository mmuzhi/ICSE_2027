class CSVProcessor:

    def read_csv(self, fileName, title, data):
        with open(fileName, 'r') as f:
            first_line = f.readline()
            if first_line == '':
                return
            if first_line.endswith('\n'):
                first_line = first_line[:-1]
            title.extend(first_line.split(','))
            for line in f:
                if line.endswith('\n'):
                    line = line[:-1]
                data.append(line.split(','))

    def write_csv(self, *args):
        nargs = len(args)
        if nargs == 3:
            title, data, fileName = args
            try:
                with open(fileName, 'w') as f:
                    f.write(','.join(title) + '\n')
                    for row in data:
                        f.write(','.join(row) + '\n')
                return 1
            except OSError:
                return 0
        elif nargs == 2:
            data, fileName = args
            try:
                with open(fileName, 'w') as f:
                    for row in data:
                        f.write(','.join(row) + '\n')
                return 1
            except OSError:
                return 0
        else:
            raise TypeError('writeCSV takes 2 or 3 arguments')

    def process_csv_data(self, N, saveFileName):
        title = []
        data = []
        self.read_csv(saveFileName, title, data)
        columnData = []
        for row in data:
            if N < len(row):
                columnData.append(row[N].upper())
        newData = [columnData]
        base_name = saveFileName.split('.')[0]
        newFileName = base_name + '_process.csv'
        return self.write_csv(title, newData, newFileName)