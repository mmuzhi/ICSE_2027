class Solution:
    def findKthBit(self, N, K, R=True):
        if N == 1:
            if K == 1:
                return '0' if R else '1'
            else:
                return '1' if not R else '0'
        mid = (1 << (N-1))
        if K < mid:
            return self.findKthBit(N-1, K, R)
        elif K == mid:
            return self.findKthBit(N-1, 2*mid - K, not R)
        else:
            return self.findKthBit(N-1, 2*mid - K, not R)