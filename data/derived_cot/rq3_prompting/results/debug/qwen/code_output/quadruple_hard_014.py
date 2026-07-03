class Solution:
    def numPermsDISequence(self, s: str) -> int:
        from functools import lru_cache
        mod = 10**9 + 7
        
        @lru_cache(maxsize=None)
        def dfs(i, last):
            if i == len(s):
                return 1
            total = 0
            if s[i] == 'D':
                for num in range(last):
                    total = (total + dfs(i+1, num)) % mod
            else:
                for num in range(last, len(s) + 1):
                    total = (total + dfs(i+1, num)) % mod
            return total % mod
        
        return dfs(0, len(s) + 1) % mod