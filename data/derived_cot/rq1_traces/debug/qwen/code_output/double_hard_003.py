class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n_val = len(s) + 1
        mod = 10**9 + 7
        
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dfs(i, last, used):
            if i == len(s):
                return 1
            total = 0
            if s[i] == 'I':
                for k in range(last + 1, n_val):
                    if not (used & (1 << k)):
                        total = (total + dfs(i + 1, k, used | (1 << k))) % mod
            else:
                for k in range(0, last):
                    if not (used & (1 << k)):
                        total = (total + dfs(i + 1, k, used | (1 << k))) % mod
            return total
        
        if n_val == 0:
            return 0
        result = 0
        for k in range(n_val):
            result = (result + dfs(0, k, 1 << k)) % mod
        return result