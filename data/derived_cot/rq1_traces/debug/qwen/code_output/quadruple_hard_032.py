from functools import lru_cache

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s)
        mod = 10**9 + 7
        
        @lru_cache(maxsize=None)
        def dfs(i, last, used):
            if i == n + 1:
                return 1
            total = 0
            if i < n:
                cond = s[i]
                for next_val in range(0, n + 1):
                    if next_val in used:
                        continue
                    if i == 0:
                        new_used = used | {next_val}
                        total = (total + dfs(i + 1, next_val, new_used)) % mod
                    else:
                        if cond == 'I':
                            if next_val > last:
                                new_used = used | {next_val}
                                total = (total + dfs(i + 1, next_val, new_used)) % mod
                        elif cond == 'D':
                            if next_val < last:
                                new_used = used | {next_val}
                                total = (total + dfs(i + 1, next_val, new_used)) % mod
            else:
                for next_val in range(0, n + 1):
                    if next_val in used:
                        continue
                    new_used = used | {next_val}
                    total = (total + dfs(i + 1, next_val, new_used)) % mod
            return total
        
        return dfs(0, None, frozenset()) % mod