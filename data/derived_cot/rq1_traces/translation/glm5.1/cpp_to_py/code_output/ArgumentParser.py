import re


class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}
        self.type_converters = {}
        self.initialize_converters()

    def parse_arguments(self, command_string):
        tokens = command_string.split()
        if not tokens:
            return (True, set())

        idx = 1  # Skip the first token (command name, consumed by getline)

        while idx < len(tokens):
            word = tokens[idx]

            if word.startswith("--"):
                key_value = word[2:]
                pos = key_value.find('=')
                if pos == -1:
                    key = key_value
                    value = ""
                else:
                    key = key_value[:pos]
                    value = key_value[pos + 1:]
                self.arguments[key] = self.convert_type(key, "1" if value == "" else value)
                idx += 1
            elif word.startswith("-"):
                key = word[1:]
                # C++ peek() after >> extraction returns whitespace (not '-'),
                # so the condition !eof() && peek()!='-' is effectively just !eof().
                # If a next token exists, it is consumed as the value.
                if idx + 1 < len(tokens):
                    value = tokens[idx + 1]
                    self.arguments[key] = self.convert_type(key, value)
                    idx += 2
                else:
                    self.arguments[key] = self.convert_type(key, "1")
                    idx += 1
            else:
                idx += 1

        missing_args = set()
        for req in self.required:
            if req not in self.arguments:
                missing_args.add(req)

        return (not missing_args, missing_args)

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

    def initialize_converters(self):
        def int_converter(value):
            try:
                # Replicate std::stoi: skip leading whitespace, parse optional sign + digits
                match = re.match(r'^\s*([+-]?\d+)', value)
                if match:
                    return str(int(match.group(1)))
                return value
            except Exception:
                return value

        def bool_converter(value):
            tmp = value
            if tmp == "True":
                tmp = "1"
            if tmp == "False":
                tmp = "0"
            return tmp

        self.type_converters["int"] = int_converter
        self.type_converters["bool"] = bool_converter