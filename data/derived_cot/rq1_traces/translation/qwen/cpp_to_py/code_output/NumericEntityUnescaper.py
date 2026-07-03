class NumericEntityUnescaper:
    @staticmethod
    def is_hex_char(c):
        c_lower = c.lower()
        return c.isdigit() or ('a' <= c_lower <= 'f')
    
    def replace(self, input_str):
        if not input_str:
            return ""
        out_list = []
        n = len(input_str)
        i = 0
        
        while i < n - 2:
            if input_str[i] == '&' and input_str[i+1] == '#':
                start = i + 2
                is_hex = False
                
                if start < n and input_str[start].lower() == 'x':
                    start += 1
                    is_hex = True
                
                j = start
                while j < n and self.is_hex_char(input_str[j]):
                    j += 1
                
                if j < n and input_str[j] == ';':
                    try:
                        num_str = input_str[start:j]
                        if is_hex:
                            entity_value = int(num_str, 16)
                        else:
                            entity_value = int(num_str, 10)
                        char_to_append = chr(entity_value)
                        out_list.append(char_to_append)
                        i = j + 1
                        continue
                    except ValueError:
                        pass
            
            out_list.append(input_str[i])
            i += 1
        
        out_list.append(input_str[i:])
        return ''.join(out_list)