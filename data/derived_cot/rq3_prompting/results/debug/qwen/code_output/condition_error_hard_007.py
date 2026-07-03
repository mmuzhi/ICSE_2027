from functools import lru_cache

class Solution:
    def numberOfArrays(self, s: str, k: int) -> int:
        n = len(s)
        mod = 10**9 + 7
        
        @lru_cache(None)
        def rec(i=0):
            if i == n:
                return 1
            res = 0
            curr = ""
            for x in range(i, n):
                curr += s[x]
                if int(curr) > k:
                    break
                res = (res + rec(x + 1)) % mod
            return res
        
        return rec() % mod