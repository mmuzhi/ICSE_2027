class CamelCaseMap:
    def __init__(self):
        self.data = {}
        self.insertion_order = []

    @staticmethod
    def to_camel_case(key):
        if not key:
            return ""
        result = []
        capitalize_next = False
        for c in key:
            if c == '_':
                capitalize_next = True
            else:
                if capitalize_next:
                    result.append(c.upper())
                    capitalize_next = False
                else:
                    result.append(c)
        return ''.join(result)

    def convert_key(self, key):
        return self.to_camel_case(key)

    def set_item(self, key, value):
        camel_key = self.convert_key(key)
        if camel_key not in self.data:
            self.insertion_order.append(camel_key)
        self.data[camel_key] = value

    def get_item(self, key):
        camel_key = self.convert_key(key)
        return self.data[camel_key]

    def del_item(self, key):
        camel_key = self.convert_key(key)
        if camel_key in self.data:
            del self.data[camel_key]
            if camel_key in self.insertion_order:
                self.insertion_order.remove(camel_key)

    def __len__(self):
        return len(self.data)

    def begin(self):
        return iter(self.insertion_order)

    def end(self):
        return iter(self.insertion_order)