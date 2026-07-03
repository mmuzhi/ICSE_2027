class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9 + 7
        n = len(s)
        dp = [1] * (n + 1)
        for i in range(n):
            new_dp = [0] * (n + 1)
            if s[i] == 'D':
                current = 0
                for j in range(i, -1, -1):
                    current = (current + dp[j + 1]) % MOD
                    new_dp[j] = current
            else:
                current = 0
                for j in range(i + 2):
                    new_dp[j] = current
                    current = (current + dp[j]) % MOD
            dp = new_dp[:i + 2]
        return dp[0] % MOD