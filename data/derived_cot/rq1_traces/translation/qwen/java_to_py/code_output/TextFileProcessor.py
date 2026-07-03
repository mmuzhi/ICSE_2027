import json
import re
from pathlib import Path

class TextFileProcessor:
    def __init__(self, file_path):
        self.file_path = file_path

    def read_file_as_json(self):
        try:
            with open(self.file_path, 'r') as file:
                return json.load(file)
        except FileNotFoundError:
            raise IOError(f"File not found: {self.file_path}")
        except json.JSONDecodeError as e:
            raise IOError(f"Failed to decode JSON: {str(e)}")

    def read_file(self):
        try:
            with open(self.file_path, 'r') as file:
                return file.read()
        except FileNotFoundError:
            raise IOError(f"File not found: {self.file_path}")
        except Exception as e:
            raise IOError(f"Error reading file: {str(e)}")

    def write_file(self, content):
        try:
            with open(self.file_path, 'w', encoding='utf-8') as file:
                file.write(content)
        except Exception as e:
            raise IOError(f"Error writing to file: {str(e)}")

    def process_file(self):
        content = self.read_file()
        processed_content = re.sub(r'[^a-zA-Z]', '', content)
        self.write_file(processed_content)
        return processed_content