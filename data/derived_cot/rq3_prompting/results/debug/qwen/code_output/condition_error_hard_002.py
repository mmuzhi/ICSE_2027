class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s)
        mod = 10**9 + 7
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dfs(i, last, used):
            if i == n:
                return 1
            total = 0
            if i == 0:
                for digit in range(0, n + 1):
                    if digit not in used:
                        total = (total + dfs(i + 1, digit, used | {digit})) % mod
            else:
                if s[i] == 'I':
                    start = last + 1
                else:
                    start = 0
                for digit in range(start, n + 1):
                    if digit not in used:
                        total = (total + dfs(i + 1, digit, used | {digit})) % mod
            return total % mod
        
        return dfs(0, None, frozenset())