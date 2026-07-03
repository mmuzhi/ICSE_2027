class BinaryDataProcessor:
    def __init__(self, binary_string: str):
        self.binary_string = self.clean_non_binary_chars(binary_string)
    
    def clean_non_binary_chars(self, input_str: str) -> str:
        return ''.join(filter(lambda c: c in '01', input_str))
    
    def calculate_binary_info(self) -> dict:
        zeroes_count = self.binary_string.count('0')
        ones_count = len(self.binary_string) - zeroes_count
        total_length = len(self.binary_string)
        
        return {
            "Zeroes": zeroes_count / total_length,
            "Ones": ones_count / total_length,
            "Bit length": total_length
        }
    
    def convert_to_ascii(self) -> str:
        num_chars = len(self.binary_string) // 8
        ascii_chars = []
        for i in range(num_chars):
            start_index = i * 8
            binary_byte = self.binary_string[start_index:start_index+8]
            if len(binary_byte) < 8:
                binary_byte = binary_byte.ljust(8, '0')  # Pad with zeros if needed
            try:
                char = chr(int(binary_byte, 2))
            except OverflowError:
                # Handle large numbers by taking modulo 256
                char = chr(int(binary_byte, 2) % 256)
            ascii_chars.append(char)
        return ''.join(ascii_chars)
    
    def convert_to_utf8(self) -> str:
        return self.convert_to_ascii()