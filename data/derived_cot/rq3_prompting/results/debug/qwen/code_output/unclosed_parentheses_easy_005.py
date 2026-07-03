class Solution:
    def f(self, n, r, count):
        if count == 32:
            return r
        bit = n & 1
        n = n >> 1
        r = (r << 1) | bit
        return self.f(n, r, count + 1)
    
    def reverseBits(self, n: int) -> int:
        n = n & 0xFFFFFFFF
        return self.f(n, 0, 0)