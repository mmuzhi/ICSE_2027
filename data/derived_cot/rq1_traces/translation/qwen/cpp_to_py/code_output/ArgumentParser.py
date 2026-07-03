class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}
        self.type_converters = {}
        self.initialize_converters()

    def initialize_converters(self):
        def convert_int(value):
            try:
                return str(int(value))
            except (ValueError, TypeError):
                return value

        def convert_bool(value):
            if value == "True":
                return "1"
            elif value == "False":
                return "0"
            else:
                return value

        self.type_converters = {
            "int": convert_int,
            "bool": convert_bool
        }

    def parse_arguments(self, command_string):
        tokens = command_string.split()
        i = 0
        n = len(tokens)
        while i < n:
            token = tokens[i]
            i += 1
            if token.startswith('--'):
                rest = token[2:]
                if '=' in rest:
                    parts = rest.split('=', 1)
                    key = parts[0]
                    value_str = parts[1] if len(parts) > 1 else ""
                else:
                    key = rest
                    value_str = ""
                self.arguments[key] = self.convert_type(key, value_str)
            elif token.startswith('-') and len(token) > 1:
                key = token[1:]
                if i < n and tokens[i].startswith('-'):
                    value_str = ""
                else:
                    value_str = tokens[i]
                    i += 1
                self.arguments[key] = self.convert_type(key, value_str)
            else:
                continue

        missing = set()
        for req in self.required:
            if req not in self.arguments:
                missing.add(req)

        return (len(missing) == 0, missing)

    def get_argument(self, key):
        return self.arguments.get(key, "")

    def add_argument(self, arg, required=False, type_str="string"):
        if required:
            self.required.add(arg)
        self.types[arg] = type_str

    def convert_type(self, key, value):
        if key in self.types:
            t = self.types[key]
            if t in self.type_converters:
                return self.type_converters[t](value)
        return value