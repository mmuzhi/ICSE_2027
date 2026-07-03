class CamelCaseMap:
    _end_sentinel = object()
    
    def __init__(self):
        self.data = {}
        self.insertion_order = []
    
    @staticmethod
    def to_camel_case(key):
        camel_case_key = []
        capitalize = False
        for c in key:
            if c == '_':
                capitalize = True
            else:
                if capitalize:
                    camel_case_key.append(c.upper())
                    capitalize = False
                else:
                    camel_case_key.append(c)
        return ''.join(camel_case_key)
    
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
        del self.data[camel_key]
        self.insertion_order.remove(camel_key)
    
    def len(self):
        return len(self.data)
    
    def begin(self):
        return iter(self.insertion_order)
    
    def end(self):
        return CamelCaseMap._end_sentinel