class Solution:
    def convertToTitle(self, n: int) -> str:
        s = ""
        while n > 0:
            n -= 1
            r = n % 26
            s = chr(65 + r) + s
            n //= 26
        return s