class NumericEntityUnescaper:

    def replace(self, string):
        if not string:
            return string

        s = string
        length = len(s)
        out_list = []
        pos = 0

        while pos < length - 2:
            if s[pos] == '&' and s[pos+1] == '#':
                start = pos + 2
                is_hex = False
                first_char = s[start] if start < length else None

                if first_char is not None and (first_char == 'x' or first_char == 'X'):
                    start += 1
                    is_hex = True

                if start >= length:
                    out_list.append(s[pos])
                    pos += 1
                    continue

                end = start
                while end < length and ( (is_hex and self.is_hex_char(s[end])) or (not is_hex and s[end].isdigit()) ):
                    end += 1

                if end < length and s[end] == ';':
                    try:
                        num_str = s[start:end]
                        base = 16 if is_hex else 10
                        entity_value = int(num_str, base)
                        entity_value = entity_value & 0xFFFF
                        out_list.append(chr(entity_value))
                        pos = end + 1
                        continue
                    except ValueError:
                        out_list.append(s[pos])
                        pos += 1
                        continue
                else:
                    out_list.append(s[pos])
                    pos += 1
                    continue
            else:
                out_list.append(s[pos])
                pos += 1

        return ''.join(out_list)

    def is_hex_char(self, c):
        if c.isdigit():
            return True
        c_lower = c.lower()
        return 'a' <= c_lower <= 'f'