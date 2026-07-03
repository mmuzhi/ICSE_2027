import os

class CSVProcessor:
    @staticmethod
    def _java_split(line):
        """Split a line like Java's String.split(",") (removes trailing empty strings)."""
        parts = line.split(',')
        while parts and parts[-1] == '':
            parts.pop()
        return parts

    def readCSV(self, fileName: str, title: list, data: list) -> None:
        with open(fileName, 'r', newline='') as reader:
            line = reader.readline()
            if line:
                line = line.rstrip('\n\r')  # remove newline, keep possible trailing spaces? Java's readLine removes newline, so we strip
                title.extend(self._java_split(line))

                for line in reader:
                    line = line.rstrip('\n\r')
                    data.append(self._java_split(line))

    def writeCSV(self, title, data, fileName: str) -> int:
        try:
            with open(fileName, 'w', newline='') as writer:
                writer.write(','.join(title))
                writer.write('\n')
                for row in data:
                    writer.write(','.join(row))
                    writer.write('\n')
            return 1
        except OSError:
            return 0

    def writeCSV(self, data, fileName: str) -> int:
        try:
            with open(fileName, 'w', newline='') as writer:
                for row in data:
                    writer.write(','.join(row))
                    writer.write('\n')
            return 1
        except OSError:
            return 0

    def processCSVData(self, N: int, saveFileName: str) -> int:
        title = []
        data = []
        self.readCSV(saveFileName, title, data)

        columnData = []
        for row in data:
            if N < len(row):
                columnData.append(row[N].upper())

        newData = [columnData]

        newFileName = saveFileName.split('.')[0] + '_process.csv'
        return self.writeCSV(title, newData, newFileName)