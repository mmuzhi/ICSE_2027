class NumberConverter:
    @staticmethod
    def _stoi_helper(s: str, base: int) -> int:
        """
        Helper method to accurately mimic C++ std::stoi behavior:
        - Skips leading ASCII whitespace.
        - Accepts optional leading '+' or '-' sign.
        - For base 16, accepts optional '0x' or '0X' prefix.
        - Stops parsing at the first character not valid for the base.
        - Throws ValueError for no valid conversion (like std::invalid_argument).
        - Throws OverflowError if the result exceeds 32-bit signed int range (like std::out_of_range).
        """
        i = 0
        n = len(s)
        
        # Skip leading ASCII whitespace
        while i < n and s[i] in " \t\n\v\f\r":
            i += 1
            
        if i == n:
            raise ValueError("invalid stoi argument")
            
        # Check for sign
        sign = 1
        if s[i] == '+':
            i += 1
        elif s[i] == '-':
            sign = -1
            i += 1
            
        # Handle 0x prefix for base 16
        if base == 16 and i < n - 1 and s[i] == '0' and s[i + 1] in ('x', 'X'):
            i += 2
            
        valid_digits = {
            2: "01",
            8: "01234567",
            16: "0123456789abcdefABCDEF"
        }[base]
        
        start = i
        while i < n and s[i] in valid_digits:
            i += 1
            
        if i == start:
            raise ValueError("invalid stoi argument")
            
        num_str = s[start:i]
        val = int(num_str, base)
        val *= sign
        
        # Mimic 32-bit signed integer overflow check of C++ std::stoi
        if val > 2147483647 or val < -2147483648:
            raise OverflowError("stoi argument out of range")
            
        return val

    @staticmethod
    def decimal_to_binary(decimal_num: int) -> str:
        # Emulates std::bitset<32> which uses 32-bit unsigned two's complement
        # format(..., 'b') natively strips leading zeros, matching the C++ erase logic
        binary_num = format(decimal_num & 0xFFFFFFFF, 'b')
        return binary_num if binary_num else "0"

    @staticmethod
    def binary_to_decimal(binary_num: str) -> int:
        return NumberConverter._stoi_helper(binary_num, 2)

    @staticmethod
    def decimal_to_octal(decimal_num: int) -> str:
        # Emulates std::oct which treats negative numbers as unsigned 32-bit
        return format(decimal_num & 0xFFFFFFFF, 'o')

    @staticmethod
    def octal_to_decimal(octal_num: str) -> int:
        return NumberConverter._stoi_helper(octal_num, 8)

    @staticmethod
    def decimal_to_hex(decimal_num: int) -> str:
        # Emulates std::hex which treats negative numbers as unsigned 32-bit
        return format(decimal_num & 0xFFFFFFFF, 'x')

    @staticmethod
    def hex_to_decimal(hex_num: str) -> int:
        return NumberConverter._stoi_helper(hex_num, 16)