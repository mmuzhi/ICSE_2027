class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}
        self.type_converters = {}
        self.initialize_converters()
    
    def initialize_converters(self):
        def int_converter(value):
            try:
                return str(int(value))
            except:
                return value
        
        def bool_converter(value):
            if value == "True":
                return "1"
            if value == "False":
                return "0"
            return value
        
        self.type_converters = {
            "int": int_converter,
            "bool": bool_converter
        }
    
    def parse_arguments(self, command_string):
        tokens = command_string.split()
        if not tokens:
            tokens = []
        else:
            tokens = tokens[1:]
        
        i = 0
        n = len(tokens)
        while i < n:
            token = tokens[i]
            if token.startswith("--"):
                key_value_part = token[2:]
                if '=' in key_value_part:
                    parts = key_value_part.split('=', 1)
                    key = parts[0]
                    value = parts[1]
                else:
                    key = key_value_part
                    value = ""
                value_to_use = value if value != "" else "1"
                self.arguments[key] = self.convert_type(key, value_to_use)
                i += 1
            elif token.startswith('-'):
                key = token[1:]
                if i + 1 < n and not tokens[i+1].startswith('-'):
                    value = tokens[i+1]
                    self.arguments[key] = self.convert_type(key, value)
                    i += 2
                else:
                    self.arguments[key] = self.convert_type(key, "1")
                    i += 1
            else:
                i += 1
        
        missing_args = set()
        for req in self.required:
            if req not in self.arguments:
                missing_args.add(req)
        return (len(missing_args) == 0, missing_args)
    
    def get_argument(self, key):
        if key in self.arguments:
            return self.arguments[key]
        return ""
    
    def add_argument(self, arg, required=False, type="string"):
        if required:
            self.required.add(arg)
        self.types[arg] = type
    
    def convert_type(self, arg, value):
        if arg not in self.types:
            return value
        type_name = self.types[arg]
        if type_name in self.type_converters:
            return self.type_converters[type_name](value)
        return value