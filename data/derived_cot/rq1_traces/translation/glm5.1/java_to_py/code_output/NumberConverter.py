class NumberConverter:

    @staticmethod
    def decimalToBinary(decimal_num: int) -> str:
        # Mask to 32 bits to handle negative numbers identically to Java's two's complement representation
        return format(decimal_num & 0xFFFFFFFF, 'b')

    @staticmethod
    def binaryToDecimal(binary_num: str) -> int:
        return NumberConverter._parse_int(binary_num, 2)

    @staticmethod
    def decimalToOctal(decimal_num: int) -> str:
        return format(decimal_num & 0xFFFFFFFF, 'o')

    @staticmethod
    def octalToDecimal(octal_num: str) -> int:
        return NumberConverter._parse_int(octal_num, 8)

    @staticmethod
    def decimalToHex(decimal_num: int) -> str:
        # 'x' ensures lowercase hex letters, matching Java's Integer.toHexString
        return format(decimal_num & 0xFFFFFFFF, 'x')

    @staticmethod
    def hexToDecimal(hex_num: str) -> int:
        return NumberConverter._parse_int(hex_num, 16)

    @staticmethod
    def _parse_int(s: str, base: int) -> int:
        # Java's Integer.parseInt does not allow a leading '+' sign
        if s.startswith('+'):
            raise ValueError(f"Invalid character '+' in string: {s}")
        
        val = int(s, base)
        
        # Java's Integer.parseInt restricts values to a 32-bit signed integer range
        if val > 2147483647 or val < -2147483648:
            raise ValueError(f"Value out of range for 32-bit signed integer: {s}")
            
        return val