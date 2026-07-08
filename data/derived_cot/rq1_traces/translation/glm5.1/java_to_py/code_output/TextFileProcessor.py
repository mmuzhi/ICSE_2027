import json
import re

class TextFileProcessor:
    def __init__(self, file_path: str):
        self.file_path = file_path

    def read_file_as_json(self) -> object:
        try:
            with open(self.file_path, 'r') as f:
                return json.load(f)
        except json.JSONDecodeError as e:
            # Jackson's ObjectMapper throws an IOException subclass for invalid JSON.
            # To keep exception behavior identical (only raising OSError/IOException equivalents),
            # we wrap Python's ValueError subclass (JSONDecodeError) in OSError.
            raise OSError(f"Invalid JSON content in {self.file_path}") from e

    def read_file(self) -> str:
        # open() defaults to the platform's standard encoding, matching Java's 
        # new String(bytes) which also uses the platform's default charset.
        with open(self.file_path, 'r') as f:
            return f.read()

    def write_file(self, content: str) -> None:
        # 'w' mode overwrites the file, matching Files.write() behavior.
        # Encoding defaults to the platform standard, matching getBytes().
        with open(self.file_path, 'w') as f:
            f.write(content)

    def process_file(self) -> str:
        content = self.read_file()
        # re.sub replaces all occurrences, identical to String.replaceAll
        processed_content = re.sub(r'[^a-zA-Z]', '', content)
        self.write_file(processed_content)
        return processed_content