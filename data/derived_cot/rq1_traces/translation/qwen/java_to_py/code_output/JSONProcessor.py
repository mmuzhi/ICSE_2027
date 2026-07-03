import json
import os

class JSONProcessor:

    @staticmethod
    def read_json(filePath):
        if not os.path.exists(filePath):
            return None
        try:
            with open(filePath, 'r') as file:
                return json.load(file)
        except Exception:
            return None

    @staticmethod
    def write_json(data, filePath):
        try:
            with open(filePath, 'w') as file:
                json.dump(data, file, indent=None)
            return True
        except Exception:
            return False

    @staticmethod
    def process_json(filePath, removeKey):
        data = JSONProcessor.read_json(filePath)
        if data is None:
            return False
        if removeKey in data:
            del data[removeKey]
            return JSONProcessor.write_json(data, filePath)
        return False