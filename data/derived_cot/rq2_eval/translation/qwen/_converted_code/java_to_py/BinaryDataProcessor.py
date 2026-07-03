class BinaryDataProcessor:
    def __init__(self, binary_string):
        self.binary_string = binary_string
        self.clean_non_binary_chars()

    def clean_non_binary_chars(self):
        self.binary_string = ''.join(bit for bit in self.binary_string if bit in '01')

    def calculate_binary_info(self):
        total_length = len(self.binary_string)
        if total_length == 0:
            return BinaryInfo(0.0, 0.0, 0)
        
        zeros_count = total_length - len(self.binary_string.replace('0', ''))
        ones_count = total_length - len(self.binary_string.replace('1', ''))
        
        zeroes_percentage = zeros_count / total_length
        ones_percentage = ones_count / total_length
        
        return BinaryInfo(zeroes_percentage, ones_percentage, total_length)

    def convert_to_ascii(self):
        result = []
        for i in range(0, len(self.binary_string), 8):
            byte_str = self.binary_string[i:i+8]
            if byte_str == '':
                continue
            decimal = int(byte_str, 2)
            result.append(chr(decimal))
        return ''.join(result)

    def get_binary_string(self):
        return self.binary_string


class BinaryInfo:
    def __init__(self, zeroes, ones, bit_length):
        self.zeroes = zeroes
        self.ones = ones
        self.bit_length = bit_length

    def __str__(self):
        return f"{{Zeroes: {self.zeroes:.3f}, Ones: {self.ones:.3f}, Bit length: {self.bit_length}}}"


if __name__ == "__main__":
    bdp = BinaryDataProcessor("0110100001100101011011000110110001101111")
    print(bdp.get_binary_string())
    print(bdp.calculate_binary_info())
    print(bdp.convert_to_ascii())