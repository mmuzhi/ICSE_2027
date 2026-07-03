from collections import defaultdict

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        mem = defaultdict(int)
        MOD = 10**9 + 7
        n = len(s)
        
        def dfs(i, val):
            if i == n:
                return 1
            if (i, val) in mem:
                return mem[i, val]
            p = 0
            if s[i] == "D":
                for ind in range(0, val):
                    p = (p + dfs(i+1, ind)) % MOD
            else:
                for ind in range(val, n - i):
                    p = (p + dfs(i+1, ind)) % MOD
            mem[i, val] = p
            return p
            
        ans = 0
        for val in range(n + 1):
            ans = (ans + dfs(0, val)) % MOD
        return ans