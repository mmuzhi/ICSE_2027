class Solution:
    def findKthBit(self, N, K, R=True):
        if N == 1:
            if K == 1:
                return '0' if R else '1'
            elif K == 2:
                return '1' if R else '0'
        mid = 1 << (N-1)
        if K <= mid:
            return self.findKthBit(N-1, K, R)
        else:
            bit = self.findKthBit(N-1, K - mid, R)
            return '1' if bit == '0' else '0'