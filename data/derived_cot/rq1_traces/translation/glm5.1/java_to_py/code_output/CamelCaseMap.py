class CamelCaseMap:
    def __init__(self):
        # dict in Python 3.7+ preserves insertion order, matching LinkedHashMap
        self.data = {}

    def get(self, key):
        return self.data.get(self._convertKey(key))

    def put(self, key, value):
        self.data[self._convertKey(key)] = value

    def remove(self, key):
        # Java's Map.remove returns the value/void but doesn't throw if missing.
        # dict.pop with a default avoids KeyError if the key doesn't exist.
        self.data.pop(self._convertKey(key), None)

    def _convertKey(self, key):
        if key is None:
            return None
        return CamelCaseMap._toCamelCase(key)

    @staticmethod
    def _toCamelCase(key):
        parts = key.split('_')
        
        # Java's split removes trailing empty strings by default, while Python keeps them.
        # We must remove trailing empty strings to match Java's behavior.
        while parts and parts[-1] == '':
            parts.pop()
            
        # If parts is empty (e.g., key was "___"), Java throws ArrayIndexOutOfBoundsException.
        # Python will throw IndexError here, which is the equivalent behavior.
        camel_case_string = [parts[0]]
        
        for i in range(1, len(parts)):
            part = parts[i]
            # If part is empty (e.g., key was "a__b"), Java throws StringIndexOutOfBoundsException.
            # Python part[0] will throw IndexError, matching the equivalent exception category.
            camel_case_string.append(part[0].upper())
            camel_case_string.append(part[1:].lower())
            
        return "".join(camel_case_string)

    def keySet(self):
        # dict.keys() returns a view of the keys, similar to Java's keySet()
        return self.data.keys()

    def size(self):
        return len(self.data)