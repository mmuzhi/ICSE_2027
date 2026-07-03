class Solution:
    def findKthBit(self, N, K, R=True):
        if N == 1:
            return '0'
        mid = (1 << (N-1))
        if K == mid:
            return '1'
        if K < mid:
            return self.findKthBit(N-1, K, R)
        else:
            return self.findKthBit(N-1, 2*mid - K, not R)