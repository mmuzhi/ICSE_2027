class Solution:
    def numPermsDISequence(self, s: str) -> int:
        n = len(s) + 1
        from collections import defaultdict
        mem = defaultdict(int)
        def dfs(i, val):
            if i == len(s):
                return 1
            if (i, val) in mem:
                return mem[(i, val)]
            p = 0
            if s[i] == 'D':
                for ind in range(0, val):
                    p = (p + dfs(i+1, ind)) % (10**9+7)
            else:
                for ind in range(val+1, n):
                    p = (p + dfs(i+1, ind)) % (10**9+7)
            mem[(i, val)] = p
            return p
        return dfs(0, 0) % (10**9+7)