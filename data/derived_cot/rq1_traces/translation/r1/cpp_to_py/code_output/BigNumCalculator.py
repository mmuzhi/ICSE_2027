class BigNumCalculator:
    @staticmethod
    def add(num1, num2):
        max_length = max(len(num1), len(num2))
        num1_padded = num1.zfill(max_length)
        num2_padded = num2.zfill(max_length)
        
        carry = 0
        result = []
        for i in range(max_length - 1, -1, -1):
            digit_sum = int(num1_padded[i]) + int(num2_padded[i]) + carry
            carry = digit_sum // 10
            digit = digit_sum % 10
            result.append(str(digit))
        
        if carry > 0:
            result.append(str(carry))
        
        result_str = ''.join(result[::-1])
        return result_str

    @staticmethod
    def subtract(num1, num2):
        num1_local = num1
        num2_local = num2
        negative = False
        
        if len(num1_local) < len(num2_local) or (len(num1_local) == len(num2_local) and num1_local < num2_local):
            num1_local, num2_local = num2_local, num1_local
            negative = True
        
        max_length = max(len(num1_local), len(num2_local))
        num1_local = num1_local.zfill(max_length)
        num2_local = num2_local.zfill(max_length)
        
        borrow = 0
        result = []
        for i in range(max_length - 1, -1, -1):
            digit_diff = int(num1_local[i]) - int(num2_local[i]) - borrow
            if digit_diff < 0:
                digit_diff += 10
                borrow = 1
            else:
                borrow = 0
            result.append(str(digit_diff))
        
        result_str = ''.join(result[::-1]).lstrip('0')
        if not result_str:
            result_str = '0'
        elif negative:
            result_str = '-' + result_str
        return result_str

    @staticmethod
    def multiply(num1, num2):
        len1 = len(num1)
        len2 = len(num2)
        result_arr = [0] * (len1 + len2)
        
        for i in range(len1 - 1, -1, -1):
            for j in range(len2 - 1, -1, -1):
                mul = int(num1[i]) * int(num2[j])
                p1 = i + j
                p2 = i + j + 1
                total = mul + result_arr[p2]
                result_arr[p1] += total // 10
                result_arr[p2] = total % 10
        
        result_str = ''.join(str(x) for x in result_arr).lstrip('0')
        return result_str if result_str != '' else '0'