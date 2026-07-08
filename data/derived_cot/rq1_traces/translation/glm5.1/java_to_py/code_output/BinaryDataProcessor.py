import re


class BinaryInfo:
    def __init__(self, zeroes, ones, bit_length):
        self.zeroes = zeroes
        self.ones = ones
        self.bit_length = bit_length

    def get_zeroes(self):
        return self.zeroes

    def get_ones(self):
        return self.ones

    def get_bit_length(self):
        return self.bit_length

    def __str__(self):
        return "{Zeroes: %.3f, Ones: %.3f, Bit length: %d}" % (self.zeroes, self.ones, self.bit_length)


class BinaryDataProcessor:
    def __init__(self, binary_string):
        self.binary_string = binary_string
        self.clean_non_binary_chars()

    def clean_non_binary_chars(self):
        self.binary_string = re.sub(r'[^01]', '', self.binary_string)

    def calculate_binary_info(self):
        zeroes_count = self.binary_string.count('0')
        ones_count = self.binary_string.count('1')
        total_length = len(self.binary_string)

        if total_length == 0:
            zeroes_percentage = float('nan')
            ones_percentage = float('nan')
        else:
            zeroes_percentage = zeroes_count / total_length
            ones_percentage = ones_count / total_length

        return BinaryInfo(zeroes_percentage, ones_percentage, total_length)

    def convert_to_ascii(self):
        result = []
        for i in range(0, len(self.binary_string), 8):
            byte_string = self.binary_string[i:i + 8]
            if len(byte_string) != 8:
                raise IndexError("String index out of range")
            decimal = int(byte_string, 2)
            result.append(chr(decimal))
        return ''.join(result)

    def convert_to_utf8(self):
        result = []
        for i in range(0, len(self.binary_string), 8):
            byte_string = self.binary_string[i:i + 8]
            if len(byte_string) != 8:
                raise IndexError("String index out of range")
            decimal = int(byte_string, 2)
            result.append(chr(decimal))
        return ''.join(result)

    def get_binary_string(self):
        return self.binary_string


if __name__ == '__main__':
    bdp = BinaryDataProcessor("0110100001100101011011000110110001101111")
    print(bdp.get_binary_string())
    print(bdp.calculate_binary_info())
    print(bdp.convert_to_ascii())
    print(bdp.convert_to_utf8())