def add(num1: str, num2: str) -> str:
    max_len = max(len(num1), len(num2))
    # pad with leading zeros
    num1 = num1.zfill(max_len)
    num2 = num2.zfill(max_len)

    carry = 0
    result = []
    for i in range(max_len - 1, -1, -1):
        digit_sum = int(num1[i]) + int(num2[i]) + carry
        carry = digit_sum // 10
        digit = digit_sum % 10
        result.insert(0, str(digit))

    if carry > 0:
        result.insert(0, str(carry))

    return ''.join(result)


def subtract(num1: str, num2: str) -> str:
    negative = False
    # ensure num1 >= num2 in absolute value (for non‑negative result)
    if len(num1) < len(num2) or (len(num1) == len(num2) and num1 < num2):
        num1, num2 = num2, num1
        negative = True

    max_len = max(len(num1), len(num2))
    num1 = num1.zfill(max_len)
    num2 = num2.zfill(max_len)

    borrow = 0
    result = []
    for i in range(max_len - 1, -1, -1):
        diff = int(num1[i]) - int(num2[i]) - borrow
        if diff < 0:
            diff += 10
            borrow = 1
        else:
            borrow = 0
        result.insert(0, str(diff))

    # strip leading zeros, keep at least one digit
    s = ''.join(result).lstrip('0')
    if not s:
        s = '0'

    if negative:
        s = '-' + s
    return s


def multiply(num1: str, num2: str) -> str:
    len1 = len(num1)
    len2 = len(num2)
    result = [0] * (len1 + len2)

    for i in range(len1 - 1, -1, -1):
        for j in range(len2 - 1, -1, -1):
            mul = int(num1[i]) * int(num2[j])
            p1 = i + j
            p2 = i + j + 1
            total = mul + result[p2]
            result[p1] += total // 10
            result[p2] = total % 10

    # skip leading zeros
    start = 0
    while start < len(result) - 1 and result[start] == 0:
        start += 1

    return ''.join(str(d) for d in result[start:])


if __name__ == '__main__':
    print(add("12345678901234567890", "98765432109876543210"))
    print(subtract("12345678901234567890", "98765432109876543210"))
    print(multiply("12345678901234567890", "98765432109876543210"))