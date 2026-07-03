class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9 + 7
        from collections import defaultdict
        mem = defaultdict(int)
        n = len(s)
        
        def dfs(i: int, less: int) -> int:
            if i == n:
                return 1
            if (i, less) in mem:
                return mem[(i, less)]
            total = 0
            if s[i] == 'D':
                # choose one of the 'less' numbers that are smaller than the current last
                for k in range(less):
                    total = (total + dfs(i + 1, k)) % MOD
            else:  # 'I'
                # choose one of the (n - i - less) numbers that are larger
                for k in range(n - i - less):
                    total = (total + dfs(i + 1, less + k)) % MOD
            mem[(i, less)] = total
            return total
        
        ans = 0
        for less in range(n + 1):
            ans = (ans + dfs(0, less)) % MOD
        return ans