class CSVProcessor:

    def read_csv(self, file_name, title, data):
        """
        Reads a CSV file and populates the title and data lists.
        Modifies title and data in-place to mimic Java's pass-by-reference behavior.
        """
        with open(file_name, 'r') as reader:
            line = reader.readline()
            if line:
                # Java's readLine() strips line terminators
                title.extend(line.rstrip('\r\n').split(','))
                
                for line_data in reader:
                    data.append(line_data.rstrip('\r\n').split(','))

    def write_csv(self, *args):
        """
        Writes data to a CSV file.
        Mimics Java method overloading based on the number of arguments:
        - write_csv(data, file_name)
        - write_csv(title, data, file_name)
        Returns 1 on success, 0 on IOException.
        """
        if len(args) == 2:
            data, file_name = args
            title = None
        elif len(args) == 3:
            title, data, file_name = args
        else:
            raise TypeError("write_csv requires 2 or 3 arguments")

        try:
            with open(file_name, 'w') as writer:
                if title is not None:
                    writer.write(','.join(title) + '\n')
                for row in data:
                    writer.write(','.join(row) + '\n')
            return 1
        except IOError:
            return 0

    def process_csv_data(self, N, save_file_name):
        """
        Processes CSV data by extracting the N-th column, converting it to uppercase,
        and writing it as a single row to a new file.
        """
        title = []
        data = []
        self.read_csv(save_file_name, title, data)

        column_data = []
        for row in data:
            if N < len(row):
                column_data.append(row[N].upper())

        new_data = []
        new_data.append(column_data)

        # Java's split("\\.") splits by literal dot. Python's split('.') does the same.
        new_file_name = save_file_name.split('.')[0] + "_process.csv"

        return self.write_csv(title, new_data, new_file_name)