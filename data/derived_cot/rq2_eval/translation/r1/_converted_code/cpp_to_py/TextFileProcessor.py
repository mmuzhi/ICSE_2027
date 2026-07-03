import json

class TextFileProcessor:
    def __init__(self, filename):
        self.filename_ = filename

    def read_file_as_json(self):
        with open(self.filename_, 'r', encoding='utf-8') as file:
            return json.load(file)

    def read_file(self):
        with open(self.filename_, 'rb') as file:
            return file.read()

    def write_file(self, content):
        with open(self.filename_, 'wb') as file:
            file.write(content)

    def process_file(self):
        content = self.read_file()
        result = bytearray()
        for byte in content:
            if (65 <= byte <= 90) or (97 <= byte <= 122):
                result.append(byte)
        result_bytes = bytes(result)
        self.write_file(result_bytes)
        return result_bytes