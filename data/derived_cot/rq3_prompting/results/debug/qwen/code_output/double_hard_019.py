from functools import lru_cache

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s) + 1
        mod = 10**9 + 7
        
        if n == 1:
            return 1
        
        @lru_cache(maxsize=None)
        def dfs(i, last, used):
            if i == n:
                return 1
            if i == 0:
                total = 0
                for j in range(n):
                    if not used.get(j, False):
                        new_used = dict(used)
                        new_used[j] = True
                        total = (total + dfs(i+1, j, new_used)) % mod
                return total
            else:
                if s[i-1] == 'I':
                    low = last + 1
                    high = n - 1
                else:
                    low = 0
                    high = last - 1
                
                total = 0
                for j in range(low, high + 1):
                    if not used.get(j, False):
                        new_used = dict(used)
                        new_used[j] = True
                        total = (total + dfs(i+1, j, new_used)) % mod
                return total
        
        return dfs(0, None, {})