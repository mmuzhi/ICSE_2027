class NumberConverter:
    @staticmethod
    def decimalToBinary(decimalNum: int) -> str:
        # Simulate Java's Integer.toBinaryString: 32-bit two's complement for negatives
        return bin(decimalNum & 0xFFFFFFFF)[2:]

    @staticmethod
    def binaryToDecimal(binaryNum: str) -> int:
        # Mimic Integer.parseInt with radix 2, including range checks for 32-bit int
        val = int(binaryNum, 2)
        if val < -2**31 or val > 2**31 - 1:
            raise ValueError("out of int range")
        return val

    @staticmethod
    def decimalToOctal(decimalNum: int) -> str:
        # Java's Integer.toOctalString: 32-bit unsigned representation for negatives
        return oct(decimalNum & 0xFFFFFFFF)[2:]

    @staticmethod
    def octalToDecimal(octalNum: str) -> int:
        val = int(octalNum, 8)
        if val < -2**31 or val > 2**31 - 1:
            raise ValueError("out of int range")
        return val

    @staticmethod
    def decimalToHex(decimalNum: int) -> str:
        # Java's Integer.toHexString: 32-bit unsigned representation for negatives
        return hex(decimalNum & 0xFFFFFFFF)[2:]

    @staticmethod
    def hexToDecimal(hexNum: str) -> int:
        val = int(hexNum, 16)
        if val < -2**31 or val > 2**31 - 1:
            raise ValueError("out of int range")
        return val