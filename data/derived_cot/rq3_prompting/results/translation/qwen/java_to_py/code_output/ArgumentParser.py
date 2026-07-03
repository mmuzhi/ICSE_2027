class ArgumentParser:
    def __init__(self):
        self.arguments = {}
        self.required = set()
        self.types = {}

    def parse_arguments(self, command_string):
        tokens = command_string.split()
        args = tokens[1:]  # Skip the first token (script name)
        i = 0
        n = len(args)
        
        while i < n:
            arg_str = args[i]
            if arg_str.startswith('--'):
                parts = arg_str.split('=', 1)
                if len(parts) == 2:
                    key = parts[0]
                    value = parts[1]
                    self.arguments[key] = self.convert_type(key, value)
                else:
                    key = arg_str[2:]
                    self.arguments[key] = True
                i += 1
            elif arg_str.startswith('-') and len(arg_str) > 1:
                key = arg_str[1:]
                if i + 1 < n and not args[i+1].startswith('-'):
                    value_str = args[i+1]
                    self.arguments[key] = self.convert_type(key, value_str)
                    i += 2
                else:
                    self.arguments[key] = True
                    i += 1
            else:
                i += 1
        
        missing_args = self.required - set(self.arguments.keys())
        if missing_args:
            return self.Tuple(False, missing_args)
        else:
            return self.Tuple(True, None)
    
    def get_argument(self, key):
        return self.arguments.get(key)
    
    def add_argument(self, arg, required, arg_type):
        if required:
            self.required.add(arg)
        self.types[arg] = arg_type
    
    def convert_type(self, arg, value):
        type_ = self.types[arg]
        if type_ == int:
            try:
                return int(value)
            except ValueError:
                return value
        elif type_ == bool:
            try:
                if value.lower() == "true":
                    return True
                else:
                    return False
            except:
                return value
        elif type_ == str:
            return value
        else:
            return value

    class Tuple:
        def __init__(self, x, y):
            self.x = x
            self.y = y

    def __str__(self):
        return f"ArgumentParser(arguments={self.arguments}, required={self.required}, types={self.types})"

# Example usage:
if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("arg1", True, int)
    parser.add_argument("arg2", False, str)
    parser.add_argument("option1", False, bool)
    parser.add_argument("option2", False, bool)

    result = parser.parse_arguments("python script.py --arg1=123 -arg2 value2 --option1 -option2")
    print(result.x)
    print(result.y)
    print(parser.arguments)