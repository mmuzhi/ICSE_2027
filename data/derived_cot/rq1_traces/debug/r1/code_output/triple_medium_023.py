class Solution:
    def addBinary(self, A, B):
        res = []
        carry = 0
        A = list(A)
        B = list(B)
        while A or B or carry:
            a = A.pop() if A else 0
            b = B.pop() if B else 0
            carry += a + b
            res.append(carry % 2)
            carry = carry // 2
        return res[::-1]

    def addNegabinary(self, A, B):
        res = []
        carry = 0
        A = list(A)
        B = list(B)
        while A or B or carry:
            a = A.pop() if A else 0
            b = B.pop() if B else 0
            carry += a + b
            res.append(carry & 1)
            carry = -(carry >> 1)
        while len(res) > 1 and res[-1] == 0:
            res.pop()
        return res[::-1]