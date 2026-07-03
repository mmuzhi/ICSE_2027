class Solution:
    def addBinary(self, A, B):
        res = []
        carry = 0
        i = len(A) - 1
        j = len(B) - 1
        while i >= 0 or j >= 0 or carry:
            a = A[i] if i >= 0 else 0
            b = B[j] if j >= 0 else 0
            total = a + b + carry
            carry = total >> 1
            res.append(total & 1)
            if i >= 0:
                i -= 1
            if j >= 0:
                j -= 1
        return res

    def addNegabinary(self, A, B):
        res = []
        carry = 0
        i = len(A) - 1
        j = len(B) - 1
        while i >= 0 or j >= 0 or carry:
            a = A[i] if i >= 0 else 0
            b = B[j] if j >= 0 else 0
            total = a + b + carry
            carry = -(total >> 1)
            res.append(total & 1)
            if i >= 0:
                i -= 1
            if j >= 0:
                j -= 1
        while len(res) > 1 and res[-1] == 0:
            res.pop()
        return res