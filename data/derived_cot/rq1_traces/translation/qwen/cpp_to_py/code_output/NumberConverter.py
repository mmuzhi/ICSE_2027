class NumberConverter:
    @staticmethod
    def decimal_to_binary(n):
        if n == 0:
            return "0"
        if n < 0:
            n_positive = n + (1 << 32)
            s = bin(n_positive)[2:]
        else:
            s = bin(n)[2:]
        if n >= 0:
            s = s.lstrip('0')
            if s == '':
                s = '0'
        return s

    @staticmethod
    def binary_to_decimal(binary_num):
        if len(binary_num) == 32 and binary_num[0] == '1':
            unsigned_value = int(binary_num, 2)
            signed_value = unsigned_value - (1 << 32)
            return signed_value
        else:
            return int(binary_num, 2)

    @staticmethod
    def decimal_to_octal(n):
        s = oct(n)[2:]
        return s

    @staticmethod
    def octal_to_decimal(octal_num):
        return int(octal_num, 8)

    @staticmethod
    def decimal_to_hex(n):
        s = hex(n)[2:]
        return s

    @staticmethod
    def hex_to_decimal(hex_num):
        return int(hex_num, 16)