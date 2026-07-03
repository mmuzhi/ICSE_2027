from collections import OrderedDict

class CamelCaseMap:
    def __init__(self):
        self._data = OrderedDict()

    def get(self, key: str) -> object:
        return self._data.get(self._convert_key(key))

    def put(self, key: str, value: object) -> None:
        self._data[self._convert_key(key)] = value

    def remove(self, key: str) -> None:
        converted = self._convert_key(key)
        if converted in self._data:
            del self._data[converted]

    def _convert_key(self, key: str) -> str:
        if key is None:
            return None
        return self._to_camel_case(key)

    @staticmethod
    def _to_camel_case(key: str) -> str:
        parts = key.split('_')
        camel = parts[0]
        for part in parts[1:]:
            # replicate Java's substring(0,1).toUpperCase() + substring(1).toLowerCase()
            # If part is empty, indexing raises IndexError (like Java's StringIndexOutOfBoundsException)
            camel += part[0].upper() + part[1:].lower()
        return camel

    def key_set(self) -> set:
        # Java returns a Set view; Python dict keys are a view, but we return a set for consistency
        return set(self._data.keys())

    def size(self) -> int:
        return len(self._data)