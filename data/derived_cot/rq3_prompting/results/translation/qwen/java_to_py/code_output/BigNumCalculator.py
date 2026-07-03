class BigNumCalculator:

    @staticmethod
    def add(num1, num2):
        max_len = max(len(num1), len(num2))
        num1 = num1.zfill(max_len)
        num2 = num2.zfill(max_len)

        carry = 0
        result = []
        for i in range(max_len-1, -1, -1):
            d1 = int(num1[i])
            d2 = int(num2[i])
            total = d1 + d2 + carry
            carry = total // 10
            digit = total % 10
            result.insert(0, digit)
        
        if carry:
            result.insert(0, carry)
        
        return ''.join(map(str, result))

    @staticmethod
    def subtract(num1, num2):
        if num1 == num2:
            return "0"
        negative = False
        if len(num1) < len(num2) or (len(num1) == len(num2) and num1 < num2):
            num1, num2 = num2, num1
            negative = True

        max_len = max(len(num1), len(num2))
        num1 = num1.zfill(max_len)
        num2 = num2.zfill(max_len)

        borrow = 0
        result = []
        for i in range(max_len-1, -1, -1):
            d1 = int(num1[i])
            d2 = int(num2[i])
            digit = d1 - d2 - borrow
            if digit < 0:
                digit += 10
                borrow = 1
            else:
                borrow = 0
            result.insert(0, digit)
        
        # Remove leading zeros
        result_str = ''.join(map(str, result)).lstrip('0')
        if result_str == '':
            result_str = '0'
        
        if negative:
            result_str = '-' + result_str
        
        return result_str

    @staticmethod
    def multiply(num1, num2):
        if num1 == '0' or num2 == '0':
            return '0'
        
        len1 = len(num1)
        len2 = len(num2)
        result_arr = [0] * (len1 + len2)

        for i in range(len1-1, -1, -1):
            for j in range(len2-1, -1, -1):
                mul = int(num1[i]) * int(num2[j])
                p1 = i + j
                p2 = i + j + 1
                total = mul + result_arr[p2]
                carry = total // 10
                result_arr[p1] += carry
                result_arr[p2] = total % 10
        
        # Remove leading zeros
        start = 0
        while start < len(result_arr) and result_arr[start] == 0:
            start += 1
        
        if start == len(result_arr):
            return '0'
        
        return ''.join(map(str, result_arr[start:]))

if __name__ == "__main__":
    calculator = BigNumCalculator()
    print(calculator.add("12345678901234567890", "98765432109876543210"))
    print(calculator.subtract("12345678901234567890", "98765432109876543210"))
    print(calculator.multiply("12345678901234567890", "98765432109876543210"))