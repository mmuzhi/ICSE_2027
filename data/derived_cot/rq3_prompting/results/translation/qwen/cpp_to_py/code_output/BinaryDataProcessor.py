class BinaryDataProcessor:
    def __init__(self, binary_string):
        self.binary_string = self.clean_non_binary_chars(binary_string)
    
    def clean_non_binary_chars(self, s):
        return ''.join(filter(lambda c: c in '01', s))
    
    def calculate_binary_info(self):
        total_length = len(self.binary_string)
        zeroes_count = self.binary_string.count('0')
        ones_count = total_length - zeroes_count
        
        zeroes_percentage = zeroes_count / total_length
        ones_percentage = ones_count / total_length
        
        return {
            "Zeroes": zeroes_percentage,
            "Ones": ones_percentage,
            "Bit length": total_length
        }
    
    def convert_to_ascii(self):
        s = []
        for i in range(0, len(self.binary_string), 8):
            chunk = self.binary_string[i:i+8]
            if chunk:
                num = 0
                for j in range(len(chunk)):
                    if chunk[j] == '1':
                        num |= (1 << (7 - j))
                s.append(chr(num))
        return ''.join(s)
    
    def convert_to_utf8(self):
        return self.convert_to_ascii()