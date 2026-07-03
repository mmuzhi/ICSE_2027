class CamelCaseMap:
    def __init__(self):
        self.data = {}

    def get(self, key):
        return self.data.get(self._convert_key(key))

    def put(self, key, value):
        self.data[self._convert_key(key)] = value

    def remove(self, key):
        self.data.pop(self._convert_key(key), None)

    def _convert_key(self, key):
        if key is None:
            return None
        return self._to_camel_case(key)

    @staticmethod
    def _to_camel_case(key):
        parts = key.split("_")
        # Java's split removes trailing empty strings, Python's split does not.
        if "_" in key:
            while parts and parts[-1] == "":
                parts.pop()
        
        # If parts is empty (e.g., key was "_"), this raises IndexError,
        # perfectly matching Java's ArrayIndexOutOfBoundsException.
        camel_case_string = [parts[0]]
        for i in range(1, len(parts)):
            part = parts[i]
            # part[0] raises IndexError if part is empty, matching Java's StringIndexOutOfBoundsException
            camel_case_string.append(part[0].upper() + part[1:].lower())
        return "".join(camel_case_string)

    def key_set(self):
        return self.data.keys()

    def size(self):
        return len(self.data)