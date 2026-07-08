import json

class TextFileProcessor:
    def __init__(self, filename: str):
        self.filename_ = filename

    def read_file_as_json(self):
        with open(self.filename_, 'r') as file:
            return json.load(file)

    def read_file(self) -> str:
        with open(self.filename_, 'r') as file:
            return file.read()

    def write_file(self, content: str) -> None:
        with open(self.filename_, 'w') as file:
            file.write(content)

    def process_file(self) -> str:
        content = self.read_file()
        
        # c.isalpha() behaves identically to C++ std::isalpha for ASCII characters.
        # For Unicode, Python's isalpha() checks a broader range of alphabetic characters,
        which is the idiomatic equivalent.
        result = ''.join(c for c in content if c.isalpha())
        
        self.write_file(result)
        return result