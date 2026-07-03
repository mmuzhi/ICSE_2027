class NumberConverter:
    MIN_INT32 = -2147483648
    MAX_INT32 = 2147483647

    @staticmethod
    def decimal_to_binary(decimalNum):
        if decimalNum < 0:
            num = decimalNum & 4294967295
            return format(num, '032b')
        else:
            return format(decimalNum, 'b')

    @staticmethod
    def binary_to_decimal(binaryNum):
        num = int(binaryNum, 2)
        if num < NumberConverter.MIN_INT32 or num > NumberConverter.MAX_INT32:
            raise ValueError('Number out of range for 32-bit signed integer')
        return num

    @staticmethod
    def decimal_to_octal(decimalNum):
        if decimalNum < 0:
            num = decimalNum & 4294967295
            return format(num, '011o')
        else:
            return format(decimalNum, 'o')

    @staticmethod
    def octal_to_decimal(octalNum):
        num = int(octalNum, 8)
        if num < NumberConverter.MIN_INT32 or num > NumberConverter.MAX_INT32:
            raise ValueError('Number out of range for 32-bit signed integer')
        return num

    @staticmethod
    def decimal_to_hex(decimalNum):
        if decimalNum < 0:
            num = decimalNum & 4294967295
            return format(num, '08x')
        else:
            return format(decimalNum, 'x')

    @staticmethod
    def hex_to_decimal(hexNum):
        num = int(hexNum, 16)
        if num < NumberConverter.MIN_INT32 or num > NumberConverter.MAX_INT32:
            raise ValueError('Number out of range for 32-bit signed integer')
        return num