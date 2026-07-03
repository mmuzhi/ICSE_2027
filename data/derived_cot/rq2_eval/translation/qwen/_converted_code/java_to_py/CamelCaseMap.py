import collections

class CamelCaseMap:

    def __init__(self):
        self._data = collections.OrderedDict()

    def __getitem__(self, key):
        camel_key = self._convert_key(key)
        return self._data.get(camel_key)

    def put(self, key, value):
        camel_key = self._convert_key(key)
        self._data[camel_key] = value

    def __delitem__(self, key):
        camel_key = self._convert_key(key)
        if camel_key in self._data:
            del self._data[camel_key]

    def keySet(self):
        return set(self._data.keys())

    def __iter__(self):
        return len(self._data)

    @staticmethod
    def _convert_key(key):
        if key is None:
            return None
        parts = key.split('_')
        if not parts:
            return key
        camel_case = parts[0]
        for part in parts[1:]:
            if part:
                camel_case += part[0].upper() + part[1:].lower()
        return camel_case