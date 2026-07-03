class BigNumCalculator:

    @staticmethod
    def add(num1, num2):
        len1 = len(num1)
        len2 = len(num2)
        maxLength = max(len1, len2)
        num1 = num1.zfill(maxLength)
        num2 = num2.zfill(maxLength)
        
        carry = 0
        result = []
        
        for i in range(maxLength-1, -1, -1):
            digit1 = int(num1[i])
            digit2 = int(num2[i])
            total = digit1 + digit2 + carry
            carry = total // 10
            result.append(str(total % 10))
        
        if carry:
            result.append(str(carry))
        result.reverse()
        return ''.join(result) if result else "0"

    @staticmethod
    def subtract(num1, num2):
        if num1 == num2:
            return "0"
        
        len1 = len(num1)
        len2 = len(num2)
        maxLength = max(len1, len2)
        num1 = num1.zfill(maxLength)
        num2 = num2.zfill(maxLength)
        
        negative = False
        if (len1 < len2) or (len1 == len2 and num1 < num2):
            negative = True
            num1, num2 = num2, num1
        
        borrow = 0
        result = []
        
        for i in range(maxLength-1, -1, -1):
            d1 = int(num1[i])
            d2 = int(num2[i])
            diff = d1 - d2 - borrow
            if diff < 0:
                diff += 10
                borrow = 1
            else:
                borrow = 0
            result.append(str(diff))
        
        # Remove leading zeros
        i = 0
        while i < len(result) - 1 and result[i] == '0':
            i += 1
        
        res_str = ''.join(result[i:]) if result else "0"
        if negative and res_str != "0":
            return '-' + res_str
        return res_str

    @staticmethod
    def multiply(num1, num2):
        if num1 == "0" or num2 == "0":
            return "0"
        
        len1 = len(num1)
        len2 = len(num2)
        result = [0] * (len1 + len2)
        
        for i in range(len1-1, -1, -1):
            digit1 = int(num1[i])
            for j in range(len2-1, -1, -1):
                digit2 = int(num2[j])
                mul = digit1 * digit2
                p1 = i + j
                p2 = i + j + 1
                total = mul + result[p2]
                result[p1] += total // 10
                result[p2] = total % 10
        
        # Remove leading zeros
        start = 0
        while start < len(result) - 1 and result[start] == 0:
            start += 1
        
        return ''.join(str(d) for d in result[start:]) if result else "0"

# Example usage:
if __name__ == "__main__":
    print(BigNumCalculator.add("12345678901234567890", "98765432109876543210"))
    print(BigNumCalculator.subtract("12345678901234567890", "98765432109876543210"))
    print(BigNumCalculator.multiply("12345678901234567890", "98765432109876543210"))