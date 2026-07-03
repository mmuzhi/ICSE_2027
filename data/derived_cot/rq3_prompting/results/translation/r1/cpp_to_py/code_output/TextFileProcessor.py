import json

class TextFileProcessor:
    def __init__(self, filename: str):
        self.filename = filename

    def read_file_as_json(self):
        with open(self.filename, 'r') as f:
            return json.load(f)

    def read_file(self) -> str:
        try:
            with open(self.filename, 'r') as f:
                return f.read()
        except FileNotFoundError:
            return ""

    def write_file(self, content: str) -> None:
        with open(self.filename, 'w') as f:
            f.write(content)

    def process_file(self) -> str:
        content = self.read_file()
        result = ''.join(c for c in content if 'a' <= c <= 'z' or 'A' <= c <= 'Z')
        self.write_file(result)
        return result