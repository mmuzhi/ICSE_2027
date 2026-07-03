import json
import os

class TextFileProcessor:
    def __init__(self, filename):
        self.filename = filename

    def read_file_as_json(self):
        with open(self.filename, 'r') as f:
            data = f.read()
        return json.loads(data)

    def read_file(self):
        with open(self.filename, 'r') as f:
            return f.read()

    def write_file(self, content):
        with open(self.filename, 'w') as f:
            f.write(content)

    def process_file(self):
        content = self.read_file()
        result = ''.join(filter(str.isalpha, content))
        self.write_file(result)
        return result