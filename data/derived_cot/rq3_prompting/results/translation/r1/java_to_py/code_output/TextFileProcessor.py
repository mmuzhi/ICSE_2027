import json
import re
from pathlib import Path


class TextFileProcessor:
    def __init__(self, file_path: str):
        self.file_path = file_path

    def read_file_as_json(self):
        with open(self.file_path, 'r') as f:
            return json.load(f)

    def read_file(self) -> str:
        return Path(self.file_path).read_text()

    def write_file(self, content: str) -> None:
        Path(self.file_path).write_text(content)

    def process_file(self) -> str:
        content = self.read_file()
        processed = re.sub(r'[^a-zA-Z]', '', content)
        self.write_file(processed)
        return processed