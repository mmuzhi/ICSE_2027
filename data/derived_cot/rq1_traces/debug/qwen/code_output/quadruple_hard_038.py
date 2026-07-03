class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s) + 1
        mod = 10**9 + 7
        from collections import defaultdict
        mem = defaultdict(int)
        
        def dfs(i, val):
            if i == len(s):
                return 1
            key = (i, val)
            if key in mem:
                return mem[key]
            p = 0
            if val is None:
                for ind in range(n):
                    p += dfs(i+1, ind) % mod
            else:
                if s[i] == 'I':
                    for ind in range(val + 1, n):
                        p += dfs(i+1, ind) % mod
                else:
                    for ind in range(0, val):
                        p += dfs(i+1, ind) % mod
            mem[key] = p % mod
            return p % mod
        
        return dfs(0, None)