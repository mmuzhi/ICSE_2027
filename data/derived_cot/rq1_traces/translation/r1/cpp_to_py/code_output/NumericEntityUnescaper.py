class NumericEntityUnescaper:
    def replace(self, input_str: str) -> str:
        if not input_str:
            return ""
        out = []
        pos = 0
        length = len(input_str)
        while pos < length - 2:
            if input_str[pos] == '&' and input_str[pos+1] == '#':
                start = pos + 2
                is_hex = False
                
                if start < length and input_str[start] in ('x', 'X'):
                    start += 1
                    is_hex = True
                
                if start == length:
                    return ''.join(out)
                
                end = start
                while end < length and self.is_hex_char(input_str[end]):
                    end += 1
                
                if end < length and input_str[end] == ';':
                    num_str = input_str[start:end]
                    if not num_str:
                        return ''.join(out)
                    
                    try:
                        if is_hex:
                            entity_value = int(num_str, 16)
                        else:
                            entity_value = int(num_str, 10)
                    except Exception:
                        return ''.join(out)
                    
                    if entity_value > 0x7FFFFFFF:
                        return ''.join(out)
                    
                    char_value = chr(entity_value & 0xFF)
                    out.append(char_value)
                    pos = end + 1
                    continue
            
            out.append(input_str[pos])
            pos += 1
        
        return ''.join(out)
    
    @staticmethod
    def is_hex_char(c):
        c_lower = c.lower()
        return '0' <= c_lower <= '9' or 'a' <= c_lower <= 'f'