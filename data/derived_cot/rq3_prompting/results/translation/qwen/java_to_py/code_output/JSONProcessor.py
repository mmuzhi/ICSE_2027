import json
from pathlib import Path

class JSONProcessor:
    def read_json(self, filepath):
        if not Path(filepath).exists():
            return None
        try:
            with open(filepath, 'r') as file:
                return json.load(file)
        except Exception:
            return None

    def write_json(self, data, filepath):
        try:
            with open(filepath, 'w') as file:
                json.dump(data, file, indent=None)
            return True
        except Exception:
            return False

    def process_json(self, filepath, remove_key):
        data = self.read_json(filepath)
        if data is None:
            return False
        if remove_key in data:
            del data[remove_key]
            return self.write_json(data, filepath)
        return False