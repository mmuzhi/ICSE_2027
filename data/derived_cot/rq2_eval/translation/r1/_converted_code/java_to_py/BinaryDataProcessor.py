class BinaryInfo:
    def __init__(self, zeroes, ones, bit_length):
        self.zeroes = zeroes
        self.ones = ones
        self.bit_length = bit_length

    def __str__(self):
        return f"{{Zeroes: {self.zeroes:.3f}, Ones: {self.ones:.3f}, Bit length: {self.bit_length}}}"

class BinaryDataProcessor:
    def __init__(self, binary_string):
        self.binary_string = binary_string
        self.clean_non_binary_chars()

    def clean_non_binary_chars(self):
        self.binary_string = ''.join(c for c in self.binary_string if c in '01')

    def calculate_binary_info(self):
        total_length = len(self.binary_string)
        zeroes_count = self.binary_string.count('0')
        ones_count = self.binary_string.count('1')
        zeroes_percentage = zeroes_count / total_length
        ones_percentage = ones_count / total_length
        return BinaryInfo(zeroes_percentage, ones_percentage, total_length)

    def convert_to_ascii(self):
        ascii_string = ""
        n = len(self.binary_string)
        for i in range(0, n, 8):
            chunk = self.binary_string[i:i+8]
            if not chunk:
                break
            decimal = int(chunk, 2)
            ascii_string += chr(decimal)
        return ascii_string

    def convert_to_utf8(self):
        utf8_string = ""
        n = len(self.binary_string)
        for i in range(0, n, 8):
            chunk = self.binary_string[i:i+8]
            if not chunk:
                break
            decimal = int(chunk, 2)
            utf8_string += chr(decimal)
        return utf8_string

    def get_binary_string(self):
        return self.binary_string

if __name__ == "__main__":
    bdp = BinaryDataProcessor("0110100001100101011011000110110001101111")
    print(bdp.get_binary_string())
    print(bdp.calculate_binary_info())
    print(bdp.convert_to_ascii())
    print(bdp.convert_to_utf8())