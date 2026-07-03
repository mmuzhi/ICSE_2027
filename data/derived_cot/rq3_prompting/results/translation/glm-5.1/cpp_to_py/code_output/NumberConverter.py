class NumberConverter:
    @staticmethod
    def decimal_to_binary(decimal_num):
        # bitset<32> gives 32-bit two's complement representation
        binary_num = bin(decimal_num & 0xFFFFFFFF)[2:]
        binary_num = binary_num.lstrip('0')
        return binary_num if binary_num else "0"

    @staticmethod
    def binary_to_decimal(binary_num):
        return int(binary_num, 2)

    @staticmethod
    def decimal_to_octal(decimal_num):
        if decimal_num < 0:
            return "-" + oct(-decimal_num)[2:]
        return oct(decimal_num)[2:]

    @staticmethod
    def octal_to_decimal(octal_num):
        return int(octal_num, 8)

    @staticmethod
    def decimal_to_hex(decimal_num):
        if decimal_num < 0:
            return "-" + hex(-decimal_num)[2:]
        return hex(decimal_num)[2:]

    @staticmethod
    def hex_to_decimal(hex_num):
        return int(hex_num, 16)