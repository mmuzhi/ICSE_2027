class CamelCaseMap:
    class _KeySet:
        def __init__(self, data_ref):
            self._data_ref = data_ref
        
        def __iter__(self):
            return iter(self._data_ref)
        
        def contains(self, key):
            return key in self._data_ref
        
        def remove(self, key):
            if key in self._data_ref:
                del self._data_ref[key]
                return True
            return False
        
        def size(self):
            return len(self._data_ref)
        
        def isEmpty(self):
            return len(self._data_ref) == 0

    def __init__(self):
        self.data = {}
    
    def get(self, key):
        converted_key = self._convertKey(key)
        return self.data.get(converted_key)
    
    def put(self, key, value):
        converted_key = self._convertKey(key)
        self.data[converted_key] = value
    
    def remove(self, key):
        converted_key = self._convertKey(key)
        if converted_key in self.data:
            del self.data[converted_key]
    
    def _convertKey(self, key):
        if key is None:
            return None
        return self._toCamelCase(key)
    
    @staticmethod
    def _toCamelCase(key):
        parts = key.split('_')
        camel_case_string = parts[0]
        for i in range(1, len(parts)):
            s = parts[i]
            camel_case_string += s[0].upper() + s[1:].lower()
        return camel_case_string
    
    def keySet(self):
        return self._KeySet(self.data)
    
    def size(self):
        return len(self.data)