def add(num1, num2):
    max_len = max(len(num1), len(num2))
    num1 = num1.zfill(max_len)
    num2 = num2.zfill(max_len)
    carry = 0
    result_chars = []
    for i in range(max_len - 1, -1, -1):
        digit1 = int(num1[i])
        digit2 = int(num2[i])
        total = digit1 + digit2 + carry
        carry = total // 10
        digit = total % 10
        result_chars.insert(0, str(digit))
    if carry:
        result_chars.insert(0, str(carry))
    return ''.join(result_chars)

def subtract(num1, num2):
    negative = False
    if len(num1) < len(num2):
        negative = True
        num1, num2 = num2, num1
    elif len(num1) == len(num2):
        if num1 < num2:
            negative = True
            num1, num2 = num2, num1
    max_len = max(len(num1), len(num2))
    num1 = num1.zfill(max_len)
    num2 = num2.zfill(max_len)
    borrow = 0
    result_chars = []
    for i in range(max_len - 1, -1, -1):
        digit1 = int(num1[i])
        digit2 = int(num2[i])
        diff = digit1 - digit2 - borrow
        if diff < 0:
            diff += 10
            borrow = 1
        else:
            borrow = 0
        result_chars.insert(0, str(diff))
    while len(result_chars) > 1 and result_chars[0] == '0':
        del result_chars[0]
    if negative:
        result_chars.insert(0, '-')
    return ''.join(result_chars)

def multiply(num1, num2):
    len1 = len(num1)
    len2 = len(num2)
    result = [0] * (len1 + len2)
    for i in range(len1 - 1, -1, -1):
        for j in range(len2 - 1, -1, -1):
            digit1 = int(num1[i])
            digit2 = int(num2[j])
            mul = digit1 * digit2
            p1 = i + j
            p2 = i + j + 1
            total = mul + result[p2]
            result[p1] += total // 10
            result[p2] = total % 10
    start = 0
    while start < len(result) - 1 and result[start] == 0:
        start += 1
    return ''.join(str(x) for x in result[start:])

if __name__ == '__main__':
    print(add("12345678901234567890", "98765432109876543210"))
    print(subtract("12345678901234567890", "98765432109876543210"))
    print(multiply("12345678901234567890", "98765432109876543210"))