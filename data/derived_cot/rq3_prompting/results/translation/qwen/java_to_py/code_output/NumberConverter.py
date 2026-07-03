class NumberConverter:

    @staticmethod
    def decimalToBinary(decimalNum):
        if decimalNum < -0x80000000 or decimalNum > 0x7FFFFFFF:
            raise OverflowError("Input is not a 32-bit integer")
        if decimalNum < 0:
            decimalNum += 0x100000000
        return bin(decimalNum)[2:]

    @staticmethod
    def binaryToDecimal(binaryNum):
        if binaryNum.startswith('-'):
            raise ValueError("Invalid input: negative sign not allowed in binary string")
        return int(binaryNum, 2)

    @staticmethod
    def decimalToOctal(decimalNum):
        if decimalNum < -0x80000000 or decimalNum > 0x7FFFFFFF:
            raise OverflowError("Input is not a 32-bit integer")
        if decimalNum < 0:
            decimalNum += 0x100000000
        return oct(decimalNum)[2:]

    @staticmethod
    def octalToDecimal(octalNum):
        if octalNum.startswith('-'):
            raise ValueError("Invalid input: negative sign not allowed in octal string")
        return int(octalNum, 8)

    @staticmethod
    def decimalToHex(decimalNum):
        if decimalNum < -0x80000000 or decimalNum > 0x7FFFFFFF:
            raise OverflowError("Input is not a 32-bit integer")
        if decimalNum < 0:
            decimalNum += 0x100000000
        return hex(decimalNum)[2:]

    @staticmethod
    def hexToDecimal(hexNum):
        if hexNum.startswith('-'):
            raise ValueError("Invalid input: negative sign not allowed in hexadecimal string")
        return int(hexNum, 16)