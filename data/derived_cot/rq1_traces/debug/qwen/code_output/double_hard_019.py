from functools import lru_cache

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s) + 1
        if n == 1:
            return 10
        
        @lru_cache(maxsize=None)
        def dfs(i, last_digit):
            if i == n:
                return 1
            total = 0
            if s[i-1] == 'D':
                for next_digit in range(0, last_digit + 1):
                    total = (total + dfs(i+1, next_digit)) % (10**9+7)
            else:
                for next_digit in range(last_digit + 1, 10):
                    total = (total + dfs(i+1, next_digit)) % (10**9+7)
            return total
        
        return dfs(1, 9) % (10**9+7)