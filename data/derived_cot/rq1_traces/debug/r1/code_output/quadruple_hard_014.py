class Solution:
    def numPermsDISequence(self, s: str) -> int:
        from collections import defaultdict
        mem = defaultdict(int)
        mod = 10**9 + 7
        
        def dfs(i, val):
            if i == len(s):
                return 1
            if (i, val) in mem:
                return mem[(i, val)]
            p = 0
            if s[i] == "D":
                for ind in range(val):
                    p += dfs(i + 1, ind)
                    p %= mod
            else:
                for ind in range(val + 1, i + 2):
                    p += dfs(i + 1, ind)
                    p %= mod
            mem[(i, val)] = p % mod
            return mem[(i, val)]
        
        total = 0
        for initial_val in range(len(s) + 1):
            total = (total + dfs(0, initial_val)) % mod
        return total