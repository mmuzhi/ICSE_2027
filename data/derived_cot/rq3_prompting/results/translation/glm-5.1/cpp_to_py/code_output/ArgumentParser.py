import re


class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}
        self.type_converters = {}
        self._initialize_converters()

    def _initialize_converters(self):
        def int_converter(value):
            m = re.match(r'^\s*([+-]?\d+)', value)
            if m:
                return str(int(m.group(1)))
            return value

        def bool_converter(value):
            if value == "True":
                return "1"
            if value == "False":
                return "0"
            return value

        self.type_converters["int"] = int_converter
        self.type_converters["bool"] = bool_converter

    def parse_arguments(self, command_string):
        words = command_string.split()
        i = 1  # skip first word (command name via getline with ' ')
        while i < len(words):
            word = words[i]
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
            elif word.startswith("-"):
                key = word[1:]
                if i + 1 < len(words) and not words[i + 1].startswith("-"):
                    value = words[i + 1]
                    self.arguments[key] = self.convert_type(key, value)
                    i += 1
                else:
                    self.arguments[key] = self.convert_type(key, "1")
            i += 1

        missing_args = {req for req in self.required if req not in self.arguments}
        return (len(missing_args) == 0, missing_args)

    def get_argument(self, key):
        return self.arguments.get(key, "")

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