class CamelCaseMap:
    _end_sentinel = object()

    def __init__(self):
        self.data = {}
        self.insertion_order = []

    @staticmethod
    def _to_camel_case(key):
        camel_case_key = []
        capitalize = False
        for c in key:
            if c == '_':
                capitalize = True
            elif capitalize:
                camel_case_key.append(c.upper())
                capitalize = False
            else:
                camel_case_key.append(c)
        return ''.join(camel_case_key)

    def _convert_key(self, key):
        return self._to_camel_case(key)

    def __setitem__(self, key, value):
        camel_key = self._convert_key(key)
        if camel_key not in self.data:
            self.insertion_order.append(camel_key)
        self.data[camel_key] = value

    def __getitem__(self, key):
        camel_key = self._convert_key(key)
        return self.data[camel_key]

    def __delitem__(self, key):
        camel_key = self._convert_key(key)
        del self.data[camel_key]
        self.insertion_order.remove(camel_key)

    def __len__(self):
        return len(self.data)

    def begin(self):
        return iter(self.insertion_order)

    def __iter__(self):
        return CamelCaseMap._end_sentinel