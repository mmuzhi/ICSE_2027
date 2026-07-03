class Solution:
    def numPermsDISequence(self, s: str) -> int:
        mem = {}
        MOD = 10**9 + 7
        
        def dfs(i, val):
            if i == len(s):
                return 1
            key = (i, val)
            if key in mem:
                return mem[key]
            p = 0
            if s[i] == "D":
                for ind in range(val):
                    p += dfs(i + 1, ind)
                    p %= MOD
            else:
                for ind in range(val + 1, len(s) + 1):
                    p += dfs(i + 1, ind)
                    p %= MOD
            mem[key] = p
            return p
        
        total = 0
        for val in range(len(s) + 1):
            total += dfs(0, val)
            total %= MOD
        return total