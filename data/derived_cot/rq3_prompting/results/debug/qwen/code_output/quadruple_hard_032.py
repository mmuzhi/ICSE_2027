class Solution:
    def numPermsDISequence(self, s: str) -> int:
        from collections import defaultdict
        mem = defaultdict(int)
        def dfs(i, val):
            if i == len(s):
                return 1
            key = (i, val)
            if key in mem:
                return mem[key]
            n_val = len(s) + 1
            p = 0
            if s[i] == 'D':
                for ind in range(0, val):
                    p = (p + dfs(i+1, ind)) % (10**9+7)
            else:
                for ind in range(val+1, n_val):
                    p = (p + dfs(i+1, ind)) % (10**9+7)
            mem[key] = p
            return p
        return dfs(0) % (10**9+7)