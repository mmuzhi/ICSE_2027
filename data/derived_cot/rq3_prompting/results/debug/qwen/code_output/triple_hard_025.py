class Solution:
    def numPermsDISequence(self, s: str) -> int:
        from collections import defaultdict
        mod = 10**9 + 7
        n = len(s)
        mem = defaultdict(int)
        def dfs(i, val=0):
            if i == n:
                return 1
            key = (i, val)
            if key in mem:
                return mem[key]
            p = 0
            if s[i] == 'D':
                for ind in range(0, val):
                    p = (p + dfs(i+1, ind)) % mod
            else:
                for ind in range(val+1, n+1):
                    p = (p + dfs(i+1, ind)) % mod
            mem[key] = p
            return p
        return dfs(0)