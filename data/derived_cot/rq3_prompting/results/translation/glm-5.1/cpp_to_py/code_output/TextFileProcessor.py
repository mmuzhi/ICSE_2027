import json as json_lib


class TextFileProcessor:
    def __init__(self, filename: str):
        self.filename_ = filename

    def read_file_as_json(self):
        with open(self.filename_, 'r') as f:
            return json_lib.load(f)

    def read_file(self) -> str:
        with open(self.filename_, 'r') as f:
            return f.read()

    def write_file(self, content: str):
        with open(self.filename_, 'w') as f:
            f.write(content)

    def process_file(self) -> str:
        content = self.read_file()
        result = ''.join(c for c in content if c.isalpha() and c.isascii())
        self.write_file(result)
        return result