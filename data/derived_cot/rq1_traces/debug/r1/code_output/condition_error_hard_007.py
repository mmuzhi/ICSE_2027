class Solution:
    def numberOfArrays(self, s: str, k: int) -> int:
        n = len(s)
        mod = 10**9 + 7

        from functools import lru_cache

        @lru_cache(maxsize=None)
        def rec(i=0):
            if i == n:
                return 1
            if s[i] == '0':
                return 0
            res = 0
            curr = ""
            for x in range(i, n):
                curr += s[x]
                num = int(curr)
                if num > k:
                    break
                res = (res + rec(x + 1)) % mod
            return res % mod

        return rec()