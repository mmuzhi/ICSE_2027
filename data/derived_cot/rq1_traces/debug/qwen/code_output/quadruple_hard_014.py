class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s) + 1
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dfs(i, last):
            if i == n:
                return 1
            total = 0
            if s[i] == 'I':
                for next_val in range(last + 1, n):
                    total = (total + dfs(i + 1, next_val)) % (10**9 + 7)
            else:
                for next_val in range(0, last):
                    total = (total + dfs(i + 1, next_val)) % (10**9 + 7)
            return total
        
        return dfs(0, -1)