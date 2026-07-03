class CSVProcessor:

    @staticmethod
    def _split(s, delimiter):
        """Mimic Java's String.split which removes trailing empty strings."""
        if not s:
            return ['']
        parts = s.split(delimiter)
        while parts and parts[-1] == '':
            parts.pop()
        return parts

    def readCSV(self, fileName, title, data):
        with open(fileName, 'r') as f:
            line = f.readline()
            if line:
                line = line.rstrip('\r\n')
                title.extend(self._split(line, ","))
                for line_data in f:
                    line_data = line_data.rstrip('\r\n')
                    data.append(self._split(line_data, ","))

    def writeCSV(self, title_or_data, data_or_filename, fileName=None):
        if fileName is None:
            data = title_or_data
            fileName = data_or_filename
            try:
                with open(fileName, 'w') as f:
                    for row in data:
                        f.write(",".join(row) + "\n")
                return 1
            except OSError:
                return 0
        else:
            title = title_or_data
            data = data_or_filename
            try:
                with open(fileName, 'w') as f:
                    f.write(",".join(title) + "\n")
                    for row in data:
                        f.write(",".join(row) + "\n")
                return 1
            except OSError:
                return 0

    def processCSVData(self, N, saveFileName):
        title = []
        data = []
        self.readCSV(saveFileName, title, data)

        columnData = []
        for row in data:
            if N < len(row):
                columnData.append(row[N].upper())

        newData = [columnData]

        return self.writeCSV(title, newData, saveFileName.split(".")[0] + "_process.csv")