class NumberConverter:

    @staticmethod
    def decimalToBinary(decimalNum: int) -> str:
        return f"{decimalNum & 0xFFFFFFFF:b}"

    @staticmethod
    def binaryToDecimal(binaryNum: str) -> int:
        if '_' in binaryNum:
            raise ValueError(f"Underscore not allowed in {binaryNum}")
        val = int(binaryNum, 2)
        if not (-0x80000000 <= val <= 0x7FFFFFFF):
            raise ValueError(f"Value out of range for int: {val}")
        return val

    @staticmethod
    def decimalToOctal(decimalNum: int) -> str:
        return f"{decimalNum & 0xFFFFFFFF:o}"

    @staticmethod
    def octalToDecimal(octalNum: str) -> int:
        if '_' in octalNum:
            raise ValueError(f"Underscore not allowed in {octalNum}")
        val = int(octalNum, 8)
        if not (-0x80000000 <= val <= 0x7FFFFFFF):
            raise ValueError(f"Value out of range for int: {val}")
        return val

    @staticmethod
    def decimalToHex(decimalNum: int) -> str:
        return f"{decimalNum & 0xFFFFFFFF:x}"

    @staticmethod
    def hexToDecimal(hexNum: str) -> int:
        if '_' in hexNum:
            raise ValueError(f"Underscore not allowed in {hexNum}")
        val = int(hexNum, 16)
        if not (-0x80000000 <= val <= 0x7FFFFFFF):
            raise ValueError(f"Value out of range for int: {val}")
        return val