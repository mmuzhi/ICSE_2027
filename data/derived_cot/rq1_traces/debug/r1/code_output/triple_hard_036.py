class Solution:
    def numPermsDISequence(self, s: str) -> int:
        from collections import defaultdict
        mem = defaultdict(int)
        MOD = 10**9 + 7

        def dfs(i, val):
            if i == len(s):
                return 1
            if (i, val) in mem:
                return mem[(i, val)]
            p = 0
            if s[i] == "D":
                for ind in range(val):
                    p += dfs(i + 1, ind)
                    p %= MOD
            else:
                for ind in range(val + 1, len(s) + 1):
                    p += dfs(i + 1, ind)
                    p %= MOD
            mem[(i, val)] = p % MOD
            return mem[(i, val)]
        
        total = 0
        for initial_val in range(len(s) + 1):
            total += dfs(0, initial_val)
            total %= MOD
        return total