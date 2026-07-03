class NumberConverter:
    MIN_INT = -2147483648
    MAX_INT = 2147483647

    @staticmethod
    def decimal_to_binary(decimal_num):
        n = decimal_num & 0xFFFFFFFF
        s = bin(n)[2:]
        s = s.lstrip('0')
        if s == '':
            return '0'
        return s

    @staticmethod
    def binary_to_decimal(binary_num):
        value = int(binary_num, 2)
        if value < NumberConverter.MIN_INT or value > NumberConverter.MAX_INT:
            raise OverflowError("integer overflow")
        return value

    @staticmethod
    def decimal_to_octal(decimal_num):
        n = decimal_num & 0xFFFFFFFF
        return format(n, 'o')

    @staticmethod
    def octal_to_decimal(octal_num):
        value = int(octal_num, 8)
        if value < NumberConverter.MIN_INT or value > NumberConverter.MAX_INT:
            raise OverflowError("integer overflow")
        return value

    @staticmethod
    def decimal_to_hex(decimal_num):
        n = decimal_num & 0xFFFFFFFF
        return format(n, 'x')

    @staticmethod
    def hex_to_decimal(hex_num):
        value = int(hex_num, 16)
        if value < NumberConverter.MIN_INT or value > NumberConverter.MAX_INT:
            raise OverflowError("integer overflow")
        return value