class NumericEntityUnescaper:
    def replace(self, string):
        hex_chars = set('0123456789abcdefABCDEF')
        out = []
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
                if start == length:
                    return ''.join(out)
                end = start
                while end < length and string[end] in hex_chars:
                    end += 1
                if end < length and string[end] == ';':
                    num_str = string[start:end]
                    base = 16 if is_hex else 10
                    try:
                        entity_value = int(num_str, base)
                        code_point = entity_value & 0xFFFF
                        out.append(chr(code_point))
                        pos = end + 1
                        continue
                    except ValueError:
                        return ''.join(out)
            out.append(string[pos])
            pos += 1
        return ''.join(out)