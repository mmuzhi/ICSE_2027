class BinaryDataProcessor:
    def __init__(self, binary_string: str):
        self.binary_string = binary_string
        self.clean_non_binary_chars()

    def clean_non_binary_chars(self):
        self.binary_string = ''.join(c for c in self.binary_string if c in '01')

    def calculate_binary_info(self) -> dict:
        total_length = len(self.binary_string)
        zeroes_count = self.binary_string.count('0')
        ones_count = total_length - zeroes_count

        if total_length == 0:
            zeroes_percentage = float('nan')
            ones_percentage = float('nan')
        else:
            zeroes_percentage = zeroes_count / float(total_length)
            ones_percentage = ones_count / float(total_length)

        return {
            "Zeroes": zeroes_percentage,
            "Ones": ones_percentage,
            "Bit length": float(total_length)
        }

    def convert_to_ascii(self) -> str:
        result = []
        for i in range(0, len(self.binary_string), 8):
            byte_str = self.binary_string[i:i+8]
            if len(byte_str) != 8:
                raise ValueError("Binary string length not a multiple of 8")
            result.append(chr(int(byte_str, 2)))
        return ''.join(result)

    def convert_to_utf8(self) -> str:
        return self.convert_to_ascii()