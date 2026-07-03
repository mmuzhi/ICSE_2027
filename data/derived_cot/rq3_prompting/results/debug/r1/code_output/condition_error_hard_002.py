from functools import lru_cache

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9 + 7
        n = len(s)

        @lru_cache(None)
        def dfs(i: int, j: int) -> int:
            # i: number of elements placed (1 ≤ i ≤ n+1)
            # j: rank of the last element (0 ≤ j < i)
            if i == 1:
                return 1 if j == 0 else 0
            total = 0
            if s[i-2] == 'I':
                for k in range(j):
                    total += dfs(i-1, k)
            else:  # 'D'
                for k in range(j, i-1):
                    total += dfs(i-1, k)
            return total % MOD

        ans = 0
        for j in range(n+1):
            ans = (ans + dfs(n+1, j)) % MOD
        return ans