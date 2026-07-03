class Solution:
    def addBinary(self, A, B):
        res = []
        carry = 0
        while A or B or carry:
            carry += (A or [0]).pop() + (B or [0]).pop()
            res.append(carry & 1)
            carry = carry >> 1
        return res[::-1]

    def addNegabinary(self, A, B):
        res = []
        carry = 0
        while A or B or carry:
            a_val = (A or [0]).pop()
            b_val = (B or [0]).pop()
            total = a_val + b_val + carry
            carry = (total - (total % 2)) // -2
            res.append(total % 2)
        while len(res) > 1 and res[-1] == 0:
            res.pop()
        return res[::-1]