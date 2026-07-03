from collections import defaultdict

class Solution:
    def numPermsDISequence(self, s: str) -> int:
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
            else:
                for ind in range(val + 1, i + 2):
                    p += dfs(i + 1, ind)
            p %= mod
            mem[(i, val)] = p
            return p
        
        total = 0
        for j in range(len(s) + 1):
            total = (total + dfs(0, j)) % mod
        return total