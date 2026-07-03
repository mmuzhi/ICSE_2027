class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        d = 1
        start = 1
        while start <= n:
            end = min(n, 10**d - 1)
            cnt = end - start + 1
            if k <= cnt:
                return start + k - 1
            else:
                k -= cnt
                d += 1
                start = 10**(d-1)