import os
import csv

class CSVProcessor:
    def read_csv(self, file_name):
        try:
            with open(file_name, 'r', newline='', encoding='utf-8') as file:
                reader = csv.reader(file)
                headers = next(reader, None)
                data = list(reader)
                return headers, data
        except FileNotFoundError:
            return [], []
        except Exception as e:
            print(f"An error occurred: {e}")
            return [], []

    def write_csv(self, data, file_name):
        try:
            with open(file_name, 'w', newline='', encoding='utf-8') as file:
                writer = csv.writer(file)
                writer.writerows(data)
            return 1
        except Exception as e:
            print(f"An error occurred: {e}")
            return 0

    def process_csv_data(self, N, save_file_name):
        headers, data = self.read_csv(save_file_name)
        if not headers or N >= len(headers) or not data:
            return 0
        
        try:
            column_data = []
            for row in data:
                if len(row) > N:
                    cell = row[N]
                    column_data.append(cell.upper())
            new_data = [headers] + [column_data]
            base_name = os.path.splitext(save_file_name)[0]
            new_file_name = f"{base_name}_process.csv"
            self.write_csv(new_data, new_file_name)
            return 1
        except Exception as e:
            print(f"An error occurred during processing: {e}")
            return 0