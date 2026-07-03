class CamelCaseMap:

    def __init__(self):
        self.data = {}
        self.insertion_order = []

    @staticmethod
    def _to_camel_case(key):
        camel_case_key = ''
        capitalize_next = False
        for c in key:
            if c == '_':
                capitalize_next = True
            elif capitalize_next:
                camel_case_key += c.upper()
                capitalize_next = False
            else:
                camel_case_key += c
        return camel_case_key

    def __setitem__(self, key, value):
        camel_key = self._to_camel_case(key)
        if camel_key not in self.data:
            self.insertion_order.append(camel_key)
        self.data[camel_key] = value

    def __getitem__(self, key):
        camel_key = self._to_camel_case(key)
        return self.data[camel_key]

    def __delitem__(self, key):
        camel_key = self._to_camel_case(key)
        if camel_key in self.data:
            del self.data[camel_key]
            self.insertion_order.remove(camel_key)

    def __len__(self):
        return len(self.data)

    def begin(self):
        return iter(self.insertion_order)

    def __iter__(self):
        return iter(())