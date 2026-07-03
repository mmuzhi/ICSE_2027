class BigNumCalculator:
    @staticmethod
    def add(num1: str, num2: str) -> str:
        max_len = max(len(num1), len(num2))
        num1_padded = '0' * (max_len - len(num1)) + num1
        num2_padded = '0' * (max_len - len(num2)) + num2

        carry = 0
        result_chars = []
        for i in range(max_len - 1, -1, -1):
            digit_sum = int(num1_padded[i]) + int(num2_padded[i]) + carry
            carry = digit_sum // 10
            digit = digit_sum % 10
            result_chars.insert(0, chr(digit + ord('0')))

        if carry > 0:
            result_chars.insert(0, chr(carry + ord('0')))

        return ''.join(result_chars)

    @staticmethod
    def subtract(num1: str, num2: str) -> str:
        n1 = num1
        n2 = num2
        negative = False

        # Ensure n1 >= n2 (absolute value)
        if len(n1) < len(n2) or (len(n1) == len(n2) and n1 < n2):
            n1, n2 = n2, n1
            negative = True

        max_len = max(len(n1), len(n2))
        n1 = '0' * (max_len - len(n1)) + n1
        n2 = '0' * (max_len - len(n2)) + n2

        borrow = 0
        result_chars = []
        for i in range(max_len - 1, -1, -1):
            digit_diff = int(n1[i]) - int(n2[i]) - borrow
            if digit_diff < 0:
                digit_diff += 10
                borrow = 1
            else:
                borrow = 0
            result_chars.insert(0, chr(digit_diff + ord('0')))

        # Remove leading zeros (but keep at least one digit)
        while len(result_chars) > 1 and result_chars[0] == '0':
            result_chars.pop(0)

        if negative:
            result_chars.insert(0, '-')

        return ''.join(result_chars)

    @staticmethod
    def multiply(num1: str, num2: str) -> str:
        len1, len2 = len(num1), len(num2)
        result = [0] * (len1 + len2)

        for i in range(len1 - 1, -1, -1):
            for j in range(len2 - 1, -1, -1):
                mul = int(num1[i]) * int(num2[j])
                p1 = i + j
                p2 = i + j + 1
                total = mul + result[p2]
                result[p1] += total // 10
                result[p2] = total % 10

        # Build result string, skip leading zeros
        parts = []
        leading_zero = True
        for digit in result:
            if digit == 0 and leading_zero:
                continue
            leading_zero = False
            parts.append(str(digit))

        return ''.join(parts) if parts else '0'