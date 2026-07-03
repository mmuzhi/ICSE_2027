class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}
        self.type_converters = {}
        self.initialize_converters()
    
    def initialize_converters(self):
        self.type_converters["int"] = self._convert_to_int
        self.type_converters["bool"] = self._convert_to_bool
        
    def _convert_to_int(self, value):
        try:
            return str(int(value))
        except Exception:
            return value
            
    def _convert_to_bool(self, value):
        tmp = value.lower()
        if tmp == "true":
            return "1"
        if tmp == "false":
            return "0"
        return value
        
    def parse_arguments(self, command_string):
        if not command_string:
            return (True, set())
            
        tokens = command_string.split()
        arguments = {}
        i = 0
        n = len(tokens)
        
        while i < n:
            word = tokens[i]
            i += 1
            if word.startswith('--'):
                # Long option
                key_value = word[2:]
                pos = key_value.find('=')
                if pos == -1:
                    key = key_value
                    value_str = "1"
                else:
                    key = key_value[:pos]
                    value_str = key_value[pos+1:]
                    if value_str == "":
                        value_str = "1"
                arguments[key] = self.convert_type(key, value_str)
            elif word.startswith('-') and word != '-':
                # Short option
                key = word[1:]
                if i < n and tokens[i][0] != '-':
                    value_str = tokens[i]
                    i += 1
                else:
                    value_str = "1"
                arguments[key] = self.convert_type(key, value_str)
                
        missing_args = set()
        for req in self.required:
            if req not in arguments:
                missing_args.add(req)
                
        return (len(missing_args) == 0, missing_args)
        
    def get_argument(self, key):
        return self.arguments.get(key, "")
        
    def add_argument(self, arg, required=False, typ="string"):
        if required:
            self.required.add(arg)
        self.types[arg] = typ
        
    def convert_type(self, arg, value):
        if arg not in self.types:
            return value
        type_str = self.types[arg]
        if type_str in self.type_converters:
            return self.type_converters[type_str](value)
        return value