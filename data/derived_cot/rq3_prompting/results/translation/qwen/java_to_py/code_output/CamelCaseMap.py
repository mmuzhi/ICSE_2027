class CamelCaseMap:
    def __init__(self):
        self.data = {}

    def get(self, key):
        return self.data.get(self._convert_key(key))

    def put(self, key, value):
        self.data[self._convert_key(key)] = value

    def remove(self, key):
        converted_key = self._convert_key(key)
        if converted_key in self.data:
            del self.data[converted_key]

    def keySet(self):
        return set(self.data.keys())

    def size(self):
        return len(self.data)

    def _convert_key(self, key):
        if key is None:
            return None
        return self._toCamelCase(key)

    @staticmethod
    def _toCamelCase(key):
        parts = key.split('_')
        if len(parts) == 0:
            return ""
        camel = parts[0]
        for i in range(1, len(parts)):
            if parts[i] == "":
                raise IndexError("String index out of range")
            camel += parts[i][0].upper() + parts[i][1:].lower()
        return camel