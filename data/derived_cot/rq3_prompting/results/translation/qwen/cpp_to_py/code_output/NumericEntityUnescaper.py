class NumericEntityUnescaper:
    def __init__(self):
        pass

    def replace(self, input_str):
        if not input_str:
            return ""
        n = len(input_str)
        output = []
        pos = 0
        while pos < n - 2:
            if input_str[pos] == '&' and input_str[pos+1] == '#':
                start = pos + 2
                is_hex = False
                if start < n and (input_str[start] == 'x' or input_str[start] == 'X'):
                    start += 1
                    is_hex = True

                if start >= n:
                    break

                end = start
                while end < n and self.is_hex_char(input_str[end]):
                    end += 1

                if end < n and input_str[end] == ';':
                    try:
                        number_str = input_str[start:end]
                        if is_hex:
                            entity_value = int(number_str, 16)
                        else:
                            entity_value = int(number_str, 10)
                        output.append(chr(entity_value))
                        pos = end + 1
                        continue
                    except Exception:
                        return ''.join(output)
            output.append(input_str[pos])
            pos += 1

        return ''.join(output)

    def is_hex_char(self, c):
        if c.isdigit():
            return True
        c_lower = c.lower()
        return 'a' <= c_lower <= 'f'