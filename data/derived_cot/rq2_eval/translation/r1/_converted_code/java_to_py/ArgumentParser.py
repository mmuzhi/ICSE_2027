class ArgumentParser:

    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}

    def parse_arguments(self, command_string):
        tokens = command_string.split()
        i = 1
        n = len(tokens)
        while i < n:
            token = tokens[i]
            if token.startswith('--'):
                key_val_str = token[2:]
                if '=' in key_val_str:
                    parts = key_val_str.split('=', 1)
                    key = parts[0]
                    value_str = parts[1]
                    self.arguments[key] = self._convert_type(key, value_str)
                else:
                    key = key_val_str
                    self.arguments[key] = True
                i += 1
            elif token.startswith('-'):
                key = token[1:]
                if i + 1 < n and (not tokens[i + 1].startswith('-')):
                    value_str = tokens[i + 1]
                    self.arguments[key] = self._convert_type(key, value_str)
                    i += 2
                else:
                    self.arguments[key] = True
                    i += 1
            else:
                i += 1
        missing_args = self.required - set(self.arguments.keys())
        if missing_args:
            return (False, missing_args)
        else:
            return (True, None)

    def get_argument(self, key):
        return self.arguments.get(key)

    def add_argument(self, arg, required, arg_type):
        if required:
            self.required.add(arg)
        self.types[arg] = arg_type

    def _convert_type(self, arg, value):
        try:
            t = self.types.get(arg)
            if t is None:
                return value
            if t is int:
                return int(value)
            elif t is bool:
                return value.lower() == 'true'
            elif t is str:
                return value
            else:
                return value
        except Exception:
            return value
if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('arg1', True, int)
    parser.add_argument('arg2', False, str)
    parser.add_argument('option1', False, bool)
    parser.add_argument('option2', False, bool)
    result = parser.parse_arguments('python script.py --arg1=123 -arg2 value2 --option1 -option2')
    print(result[0])
    print(result[1])
    print(parser.arguments)