class BigNumCalculator:
    @staticmethod
    def add(num1, num2):
        n = max(len(num1), len(num2))
        num1_padded = num1.rjust(n, '0')
        num2_padded = num2.rjust(n, '0')
        carry = 0
        result_digits = []
        for i in range(n-1, -1, -1):
            d1 = int(num1_padded[i])
            d2 = int(num2_padded[i])
            s = d1 + d2 + carry
            carry = s // 10
            digit = s % 10
            result_digits.append(str(digit))
        if carry:
            result_digits.append(str(carry))
        result_str = ''.join(result_digits[::-1]).lstrip('0')
        return result_str if result_str else '0'
    
    @staticmethod
    def subtract(num1, num2):
        if num1 == num2:
            return "0"
        n1 = num1
        n2 = num2
        negative = False
        if len(n1) < len(n2) or (len(n1) == len(n2) and n1 < n2):
            n1, n2 = n2, n1
            negative = True
        n = max(len(n1), len(n2))
        n1_padded = n1.rjust(n, '0')
        n2_padded = n2.rjust(n, '0')
        borrow = 0
        result_digits = []
        for i in range(n-1, -1, -1):
            d1 = int(n1_padded[i])
            d2 = int(n2_padded[i])
            diff = d1 - d2 - borrow
            if diff < 0:
                diff += 10
                borrow = 1
            else:
                borrow = 0
            result_digits.append(str(diff))
        result_str = ''.join(result_digits[::-1]).lstrip('0')
        result_str = result_str if result_str else '0'
        if negative:
            result_str = '-' + result_str
        return result_str
    
    @staticmethod
    def multiply(num1, num2):
        if num1 == "0" or num2 == "0":
            return "0"
        len1 = len(num1)
        len2 = len(num2)
        result = [0] * (len1 + len2)
        for i in range(len1-1, -1, -1):
            for j in range(len2-1, -1, -1):
                mul = (ord(num1[i]) - ord('0')) * (ord(num2[j]) - ord('0'))
                p1 = i + j
                p2 = i + j + 1
                total = mul + result[p2]
                carry = total // 10
                result[p1] += carry
                result[p2] = total % 10
        leading_zero = True
        output_str = []
        for digit in result:
            if digit == 0 and leading_zero:
                continue
            leading_zero = False
            output_str.append(str(digit))
        return ''.join(output_str) if output_str else "0"