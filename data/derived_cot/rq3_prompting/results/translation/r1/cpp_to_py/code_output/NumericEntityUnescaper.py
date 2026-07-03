class NumericEntityUnescaper:
    @staticmethod
    def is_hex_char(c: str) -> bool:
        return c.isdigit() or ('a' <= c.lower() <= 'f')

    def replace(self, input_str: str) -> str:
        out_chars = []
        length = len(input_str)
        if length == 0:
            return ""
        pos = 0
        while pos < length - 2:
            if input_str[pos] == '&' and input_str[pos + 1] == '#':
                start = pos + 2
                is_hex = False
                if start < length and (input_str[start] == 'x' or input_str[start] == 'X'):
                    start += 1
                    is_hex = True
                if start == length:
                    return "".join(out_chars)
                end = start
                while end < length and NumericEntityUnescaper.is_hex_char(input_str[end]):
                    end += 1
                if end < length and input_str[end] == ';':
                    try:
                        number_str = input_str[start:end]
                        if is_hex:
                            entity_value = int(number_str, 16)
                        else:
                            entity_value = int(number_str)
                        # Simulate C++ truncation to 8-bit char
                        out_chars.append(chr(entity_value % 256))
                        pos = end + 1
                        continue
                    except (ValueError, OverflowError):  # ss.fail() equivalent
                        return "".join(out_chars)
            out_chars.append(input_str[pos])
            pos += 1
        return "".join(out_chars)