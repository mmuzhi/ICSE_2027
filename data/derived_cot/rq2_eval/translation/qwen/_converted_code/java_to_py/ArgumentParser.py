import sys
from typing import Dict, Set, Optional, Tuple

class ArgumentParser:

    def __init__(self):
        self.arguments: Dict[str, object] = {}
        self.required: Set[str] = set()
        self.types: Dict[str, type] = {}

    def parse_arguments(self, command_string: str) -> Tuple[bool, Optional[Set[str]]]:
        args = command_string.split()
        for i in range(1, len(args)):
            arg = args[i]
            if arg.startswith('--'):
                rest = arg[2:]
                parts = rest.split('=', 1)
                key = parts[0]
                if len(parts) == 2:
                    value = parts[1]
                    self.arguments[key] = self._convert_type(key, value)
                else:
                    self.arguments[key] = True
            elif arg.startswith('-'):
                key = arg[1:]
                if i + 1 < len(args) and (not args[i + 1].startswith('-')):
                    value = args[i + 1]
                    self.arguments[key] = self._convert_type(key, value)
                    i += 1
                else:
                    self.arguments[key] = True
        missing_args = set(self.required)
        if self.arguments:
            missing_args -= set(self.arguments.keys())
        if missing_args:
            return (False, missing_args)
        return (True, None)

    def get_argument(self, key: str) -> Optional[object]:
        return self.arguments.get(key)

    def add_argument(self, arg: str, required: bool, arg_type: type) -> None:
        self.types[arg] = arg_type
        if required:
            self.required.add(arg)

    def _convert_type(self, arg: str, value: str) -> object:
        t = self.types.get(arg)
        if t is None:
            return value
        try:
            if t == int:
                return int(value)
            elif t == bool:
                return value.lower() in ['true', 'yes', '1']
            elif t == str:
                return value
        except Exception:
            return value
        return value
if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('arg1', True, int)
    parser.add_argument('arg2', False, str)
    parser.add_argument('option1', False, bool)
    parser.add_argument('option2', False, bool)
    command_string = 'python script.py --arg1=123 -arg2 value2 --option1 -option2'
    result = parser.parse_arguments(command_string)
    print(result[0])
    if result[1] is not None:
        print(result[1])
    print(parser.arguments)