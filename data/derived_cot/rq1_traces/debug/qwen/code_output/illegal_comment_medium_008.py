class Solution:
    def addBinary(self, A, B):
        A = list(map(int, list(A)))[::-1]
        B = list(map(int, list(B)))[::-1]
        res = []
        carry = 0
        while A or B or carry:
            a = A.pop() if A else 0
            b = B.pop() if B else 0
            carry += a + b
            res.append(carry & 1)
            carry = carry >> 1
        res_str = ''.join(str(x) for x in res[::-1])
        return res_str.lstrip('0') or '0'
    
    def addNegabinary(self, A, B):
        A = list(map(int, list(A)))[::-1]
        B = list(map(int, list(B)))[::-1]
        res = []
        carry = 0
        while A or B or carry:
            a = A.pop() if A else 0
            b = B.pop() if B else 0
            carry += a + b
            res.append(carry & 1)
            carry = -(carry >> 1)
        res_str = ''.join(str(x) for x in res[::-1])
        return res_str.lstrip('0') or '0'