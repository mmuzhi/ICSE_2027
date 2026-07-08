import json
import os

class JSONProcessor:
    def read_json(self, file_path):
        """
        Reads a JSON file.
        To emulate the C++ output parameter `nlohmann::json& output`, 
        this method returns a tuple (status_code, data).
        
        status_code:
            1: Success
            0: File could not be opened
           -1: Parsing error or JSON is null
        """
        try:
            with open(file_path, 'r') as file:
                data = json.load(file)
        except (FileNotFoundError, PermissionError, OSError):
            # C++ returns 0 if !file.is_open()
            return 0, None
        except (json.JSONDecodeError, Exception):
            # C++ catches (...) and returns -1 for parsing errors
            return -1, None

        if data is None:
            # C++ returns -1 if output.is_null()
            return -1, None

        return 1, data

    def write_json(self, data, file_path):
        """
        Writes JSON data to a file.
        Returns:
            1: Success
           -1: File could not be opened or write failed
        """
        try:
            with open(file_path, 'w') as file:
                # data.dump(4) in C++ nlohmann::json translates to indent=4
                file.write(json.dumps(data, indent=4))
        except (OSError, Exception):
            # C++ returns -1 if !file.is_open() or catches (...) during write
            return -1

        return 1

    def process_json(self, file_path, remove_key):
        # C++ passes output by reference; Python uses tuple unpacking
        result, data = self.read_json(file_path)

        if result != 1:
            return 0

        # C++ data.contains() is designed for objects. We check for dict.
        if isinstance(data, dict) and remove_key in data:
            del data[remove_key]
            return self.write_json(data, file_path)
        else:
            return 0