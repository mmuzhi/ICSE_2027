import re

class BinaryDataProcessor:
    def __init__(self, binary_string):
        self.binary_string = binary_string
        self.clean_non_binary_chars()

    def clean_non_binary_chars(self):
        self.binary_string = re.sub(r'[^01]', '', self.binary_string)

    def calculate_binary_info(self):
        total_length = len(self.binary_string)
        ones_count = total_length - len(self.binary_string.replace('0', ''))
        zeros_count = total_length - len(self.binary_string.replace('1', ''))
        zeros_percentage = zeros_count / total_length
        ones_percentage = ones_count / total_length
        return BinaryInfo(zeros_percentage, ones_percentage, total_length)

    def convert_to_ascii(self):
        return self._convert_binary_to_string()

    def convert_to_utf8(self):
        return self._convert_binary_to_string()

    def _convert_binary_to_string(self):
        chars = []
        for i in range(0, len(self.binary_string), 8):
            byte_str = self.binary_string[i:i+8]
            decimal = int(byte_str, 2)
            chars.append(chr(decimal))
        return ''.join(chars)

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
    print(bdp.convert_to_utf8())