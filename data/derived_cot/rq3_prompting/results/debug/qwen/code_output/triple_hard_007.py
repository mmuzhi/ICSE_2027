class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s)
        mod = 10**9 + 7
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dfs(i, last, mask):
            if i == n + 1:
                return 1
            total = 0
            if i == 0:
                for digit in range(10):
                    new_mask = mask | (1 << digit)
                    total = (total + dfs(i + 1, digit, new_mask)) % mod
            else:
                if s[i - 1] == 'I':
                    for digit in range(last + 1, 10):
                        if not (mask & (1 << digit)):
                            new_mask = mask | (1 << digit)
                            total = (total + dfs(i + 1, digit, new_mask)) % mod
                else:
                    for digit in range(0, last):
                        if not (mask & (1 << digit)):
                            new_mask = mask | (1 << digit)
                            total = (total + dfs(i + 1, digit, new_mask)) % mod
            return total % mod
        
        return dfs(0, -1, 0) % mod