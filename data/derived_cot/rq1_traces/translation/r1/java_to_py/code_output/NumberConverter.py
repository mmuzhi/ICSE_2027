class NumberConverter:
    MIN_INT32 = -2147483648
    MAX_INT32 = 2147483647

    @staticmethod
    def decimalToBinary(decimalNum):
        if decimalNum < 0:
            num = decimalNum & 0xFFFFFFFF
            return format(num, '032b')
        else:
            return format(decimalNum, 'b')
    
    @staticmethod
    def binaryToDecimal(binaryNum):
        num = int(binaryNum, 2)
        if num < NumberConverter.MIN_INT32 or num > NumberConverter.MAX_INT32:
            raise ValueError("Number out of range for 32-bit signed integer")
        return num
    
    @staticmethod
    def decimalToOctal(decimalNum):
        if decimalNum < 0:
            num = decimalNum & 0xFFFFFFFF
            return format(num, '011o')
        else:
            return format(decimalNum, 'o')
    
    @staticmethod
    def octalToDecimal(octalNum):
        num = int(octalNum, 8)
        if num < NumberConverter.MIN_INT32 or num > NumberConverter.MAX_INT32:
            raise ValueError("Number out of range for 32-bit signed integer")
        return num
    
    @staticmethod
    def decimalToHex(decimalNum):
        if decimalNum < 0:
            num = decimalNum & 0xFFFFFFFF
            return format(num, '08x')
        else:
            return format(decimalNum, 'x')
    
    @staticmethod
    def hexToDecimal(hexNum):
        num = int(hexNum, 16)
        if num < NumberConverter.MIN_INT32 or num > NumberConverter.MAX_INT32:
            raise ValueError("Number out of range for 32-bit signed integer")
        return num