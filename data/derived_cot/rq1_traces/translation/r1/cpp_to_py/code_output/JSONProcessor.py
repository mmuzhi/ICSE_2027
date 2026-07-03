import json

class JSONProcessor:
    def read_json(self, file_path):
        try:
            with open(file_path, 'r') as f:
                data = json.load(f)
        except OSError:
            return 0, None
        except Exception:
            return -1, None
        
        if data is None:
            return -1, None
            
        return 1, data

    def write_json(self, data, file_path):
        try:
            with open(file_path, 'w') as f:
                json.dump(data, f, indent=4)
        except Exception:
            return -1
        return 1

    def process_json(self, file_path, remove_key):
        result, data = self.read_json(file_path)
        if result != 1:
            return 0
            
        if isinstance(data, dict) and remove_key in data:
            del data[remove_key]
            return self.write_json(data, file_path)
        else:
            return 0