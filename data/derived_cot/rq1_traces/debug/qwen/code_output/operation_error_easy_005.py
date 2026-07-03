class Solution:
    def f(self, n, r, count):
        if count == 32:
            return r
        bit = (n >> count) & 1
        if bit:
            r |= (1 << (31 - count))
        return self.f(n, r, count + 1)
    
    def reverseBits(self, n: int) -> int:
        return self.f(n, 0, 0)