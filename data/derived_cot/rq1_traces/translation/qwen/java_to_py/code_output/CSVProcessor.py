import os

class CSVProcessor:

    @staticmethod
    def read_csv(fileName, title, data):
        with open(fileName, 'r', encoding=None) as file:
            first_line = file.readline()
            if first_line is not None:
                title.extend(first_line.split(','))
                for line in file:
                    data.append(line.split(','))

    @staticmethod
    def write_csv_with_title(title, data, fileName):
        with open(fileName, 'w', encoding=None) as file:
            file.write(','.join(title))
            file.write(os.linesep)
            for row in data:
                file.write(','.join(row))
                file.write(os.linesep)
        return 1

    @staticmethod
    def write_csv_without_title(data, fileName):
        with open(fileName, 'w', encoding=None) as file:
            for row in data:
                file.write(','.join(row))
                file.write(os.linesep)
        return 1

    @staticmethod
    def process_csv_data(N, saveFileName):
        title = []
        data = []
        try:
            CSVProcessor.read_csv(saveFileName, title, data)
        except IOError as e:
            raise IOError(e)
        
        columnData = []
        for row in data:
            if N < len(row):
                columnData.append(row[N].upper())
        
        newData = [columnData]
        
        try:
            result = CSVProcessor.write_csv_with_title(title, newData, saveFileName.split('.')[0] + '_process.csv')
        except IOError as e:
            raise IOError(e)
        
        return 1