import math

class BinaryDataProcessor:
    def __init__(self, binary_string: str):
        self.binary_string = binary_string
        self.clean_non_binary_chars()

    def clean_non_binary_chars(self):
        # Removes all characters that are not '0' or '1'
        self.binary_string = "".join(c for c in self.binary_string if c in "01")

    def calculate_binary_info(self):
        zeroes_count = self.binary_string.count('0')
        ones_count = len(self.binary_string) - zeroes_count
        total_length = len(self.binary_string)

        # C++ float division by zero results in NaN, whereas Python raises ZeroDivisionError.
        # We mimic the C++ behavior by checking for zero length explicitly.
        if total_length == 0:
            zeroes_percentage = float('nan')
            ones_percentage = float('nan')
        else:
            zeroes_percentage = zeroes_count / total_length
            ones_percentage = ones_count / total_length

        return {
            "Zeroes": zeroes_percentage,
            "Ones": ones_percentage,
            "Bit length": float(total_length)
        }

    def convert_to_ascii(self):
        chars = []
        # Process the binary string in chunks of 8 bits
        for i in range(0, len(self.binary_string), 8):
            byte_str = self.binary_string[i:i+8]
            # int(str, 2) perfectly mimics std::bitset<8>(str).to_ulong() 
            # by implicitly handling leading zeros for substrings shorter than 8 chars.
            chars.append(chr(int(byte_str, 2)))
        return "".join(chars)

    def convert_to_utf8(self):
        return self.convert_to_ascii()