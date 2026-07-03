import json

class JSONProcessor:
    
    def read_json(self, file_path, output):
        try:
            with open(file_path, 'r') as file:
                data = json.load(file)
                output = data
                return 1
        except FileNotFoundError:
            return 0
        except json.JSONDecodeError:
            return -1
        except Exception:
            return -1

    def write_json(self, data, file_path):
        try:
            with open(file_path, 'w') as file:
                json.dump(data, file, indent=4)
            return 1
        except Exception:
            return -1

    def process_json(self, file_path, remove_key):
        data = None
        result = self.read_json(file_path, data)
        if result != 1:
            return 0
        
        if remove_key in data:
            del data[remove_key]
            return self.write_json(data, file_path)
        else:
            return 0