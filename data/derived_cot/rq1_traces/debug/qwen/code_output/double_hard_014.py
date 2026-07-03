class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        x = 1
        while x <= n:
            count = min(n, x*10-1) - x + 1
            if k <= count:
                return x + k - 1
            else:
                k -= count
                x *= 10