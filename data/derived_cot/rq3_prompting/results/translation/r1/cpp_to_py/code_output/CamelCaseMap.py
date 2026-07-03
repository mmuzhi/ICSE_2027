class CamelCaseMap:
    def __init__(self):
        self.data = {}
        self.insertion_order = []

    @staticmethod
    def to_camel_case(key):
        camel_key = []
        capitalize = False
        for ch in key:
            if ch == '_':
                capitalize = True
            else:
                camel_key.append(ch.upper() if capitalize else ch)
                capitalize = False
        return ''.join(camel_key)

    def convert_key(self, key):
        return self.to_camel_case(key)

    def set_item(self, key, value):
        camel_key = self.convert_key(key)
        if camel_key not in self.data:
            self.insertion_order.append(camel_key)
        self.data[camel_key] = value

    def get_item(self, key):
        return self.data[self.convert_key(key)]

    def del_item(self, key):
        camel_key = self.convert_key(key)
        self.data.pop(camel_key, None)
        if camel_key in self.insertion_order:
            self.insertion_order.remove(camel_key)

    def len(self):
        return len(self.data)

    def __iter__(self):
        return iter(self.insertion_order)

    def __len__(self):
        return len(self.data)