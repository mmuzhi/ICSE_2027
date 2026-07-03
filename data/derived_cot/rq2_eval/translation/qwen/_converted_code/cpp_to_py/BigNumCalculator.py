class BigNumCalculator:
    @staticmethod
    def add(num1, num2):
        if num1 == "" or num1 is None:
            num1 = "0"
        if num2 == "" or num2 is None:
            num2 = "0"
        
        max_length = max(len(num1), len(num2))
        num1_padded = '0' * (max_length - len(num1)) + num1
        num2_padded = '0' * (max_length - len(num2)) + num2
        
        carry = 0
        digits = []
        for i in range(max_length-1, -1, -1):
            digit_sum = int(num1_padded[i]) + int(num2_padded[i]) + carry
            carry = digit_sum // 10
            digit = digit_sum % 10
            digits.append(str(digit))
            
        if carry:
            digits.append(str(carry))
            
        digits.reverse()
        return ''.join(digits)
    
    @staticmethod
    def subtract(num1, num2):
        if num1 == "" or num1 is None:
            num1 = "0"
        if num2 == "" or num2 is None:
            num2 = "0"
            
        if len(num1) < len(num2) or (len(num1) == len(num2) and num1 < num2):
            num1, num2 = num2, num1
            negative = True
        else:
            negative = False
            
        max_length = max(len(num1), len(num2))
        num1_padded = '0' * (max_length - len(num1)) + num1
        num2_padded = '0' * (max_length - len(num2)) + num2
        
        borrow = 0
        digits = []
        for i in range(max_length-1, -1, -1):
            digit_diff = int(num1_padded[i]) - int(num2_padded[i]) - borrow
            if digit_diff < 0:
                digit_diff += 10
                borrow = 1
            else:
                borrow = 0
            digits.append(str(digit_diff))
            
        result_str = ''.join(digits)[::-1]
        i = 0
        n = len(result_str)
        while i < n and result_str[i] == '0':
            i += 1
        if i == n:
            result_str = "0"
        else:
            result_str = result_str[i:]
            
        if negative:
            result_str = '-' + result_str
            
        return result_str

    @staticmethod
    def multiply(num1, num2):
        if num1 == "" or num1 is None:
            num1 = "0"
        if num2 == "" or num2 is None:
            num2 = "0"
            
        len1 = len(num1)
        len2 = len(num2)
        res = [0] * (len1 + len2)
        
        for i in range(len1-1, -1, -1):
            for j in range(len2-1, -1, -1):
                mul = int(num1[i]) * int(num2[j])
                p1 = i + j
                p2 = i + j + 1
                total = mul + res[p2]
                res[p1] += total // 10
                res[p2] = total % 10
                
        leading_zero = True
        result_str = ""
        for num in res:
            if num == 0 and leading_zero:
                continue
            leading_zero = False
            result_str += str(num)
            
        if result_str == "":
            return "0"
        return result_str