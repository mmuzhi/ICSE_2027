class Solution:
    def findKthBit(self, N, K, R=True):
        if K == 1:
            return '0' if R else '1'
        mid = (1 << (N - 1))
        if K < mid:
            return self.findKthBit(N - 1, K, R)
        elif K == mid:
            return self.findKthBit(N - 1, mid, not R)
        else:
            j = K - mid
            pos = mid - j + 1
            return self.findKthBit(N - 1, pos, not R)