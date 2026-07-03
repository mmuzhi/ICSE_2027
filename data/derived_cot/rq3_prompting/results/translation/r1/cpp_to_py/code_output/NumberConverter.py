class NumberConverter:
    @staticmethod
    def decimal_to_binary(decimal_num):
        # 32‑bit unsigned representation to match std::bitset<32>
        unsigned_val = decimal_num & 0xFFFFFFFF
        binary_str = format(unsigned_val, '032b')
        # Remove leading zeros, but keep at least one digit
        stripped = binary_str.lstrip('0')
        return '0' if stripped == '' else stripped

    @staticmethod
    def binary_to_decimal(binary_num):
        return int(binary_num, 2)

    @staticmethod
    def decimal_to_octal(decimal_num):
        return format(decimal_num, 'o')

    @staticmethod
    def octal_to_decimal(octal_num):
        return int(octal_num, 8)

    @staticmethod
    def decimal_to_hex(decimal_num):
        return format(decimal_num, 'x')

    @staticmethod
    def hex_to_decimal(hex_num):
        return int(hex_num, 16)