class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}
        self.type_converters = {}
        self.initialize_converters()

    def parse_arguments(self, command_string):
        # Skip the first token (program name) as in C++:
        # std::getline(iss, word, ' ') reads until first space.
        idx = command_string.find(' ')
        if idx == -1:
            rest = ''
        else:
            rest = command_string[idx+1:]
        # Split rest by whitespace (matching >> extraction)
        tokens = rest.split() if rest else []

        i = 0
        while i < len(tokens):
            word = tokens[i]
            if word.startswith('--'):
                # --key=value or --key (value defaults to "1")
                key_value = word[2:]
                pos = key_value.find('=')
                if pos == -1:
                    key = key_value
                    value = '1'
                else:
                    key = key_value[:pos]
                    value = key_value[pos+1:]
                    if value == '':
                        value = '1'
                self.arguments[key] = self.convert_type(key, value)
                i += 1
            elif word.startswith('-'):
                # -key value or -key (value defaults to "1")
                key = word[1:]
                # Peek at next token: if exists and doesn't start with '-', use it as value.
                if i + 1 < len(tokens) and not tokens[i+1].startswith('-'):
                    value = tokens[i+1]
                    i += 2
                else:
                    value = '1'
                    i += 1
                self.arguments[key] = self.convert_type(key, value)
            else:
                # Words not starting with dash are ignored (like the C++ while loop does)
                i += 1

        missing_args = {req for req in self.required if req not in self.arguments}
        return (len(missing_args) == 0, missing_args)

    def get_argument(self, key):
        return self.arguments.get(key, '')

    def add_argument(self, arg, required=False, type_='string'):
        if required:
            self.required.add(arg)
        self.types[arg] = type_

    def convert_type(self, arg, value):
        if arg not in self.types:
            return value
        type_ = self.types[arg]
        converter = self.type_converters.get(type_)
        return converter(value) if converter else value

    def initialize_converters(self):
        def int_converter(value):
            try:
                return str(int(value))
            except Exception:
                return value
        def bool_converter(value):
            if value == 'True':
                return '1'
            if value == 'False':
                return '0'
            return value
        self.type_converters['int'] = int_converter
        self.type_converters['bool'] = bool_converter