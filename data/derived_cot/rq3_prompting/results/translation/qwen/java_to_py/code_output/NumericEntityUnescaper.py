class NumericEntityUnescaper:

    def replace(self, string):
        out_list = []
        pos = 0
        length = len(string)
        while pos < length - 2:
            if string[pos] == '&' and string[pos+1] == '#':
                start = pos + 2
                is_hex = False
                first_char = string[start]
                if first_char == 'x' or first_char == 'X':
                    start += 1
                    is_hex = True
                if start >= length:
                    break
                end = start
                while end < length and self.is_hex_char(string[end], is_hex):
                    end += 1
                if end < length and string[end] == ';':
                    entity_str = string[start:end]
                    try:
                        entity_value = int(entity_str, base=16 if is_hex else 10)
                        code = entity_value & 0xFFFF
                        out_list.append(chr(code))
                        pos = end + 1
                        continue
                    except ValueError:
                        return ''.join(out_list)
            out_list.append(string[pos])
            pos += 1
        return ''.join(out_list)

    def is_hex_char(self, c, is_hex):
        if is_hex:
            if c.isdigit():
                return True
            c_low = c.lower()
            return 'a' <= c_low <= 'f'
        else:
            return c.isdigit()