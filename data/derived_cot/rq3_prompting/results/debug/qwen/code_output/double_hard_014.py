class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        x = 1
        while True:
            cnt = min(n, x*10-1) - x + 1
            if k <= cnt:
                return x + k - 1
            else:
                k -= cnt
                x *= 10