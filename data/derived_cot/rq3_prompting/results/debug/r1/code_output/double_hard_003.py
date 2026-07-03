class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10 ** 9 + 7
        n = len(s)
        dp = [1] * (n + 1)                     # dp[j] for length 1 (one number)
        for ch in s:
            new_dp = [0] * (n + 1)
            if ch == 'I':
                prefix = 0
                for j in range(n + 1):
                    new_dp[j] = prefix
                    prefix = (prefix + dp[j]) % MOD
            else:                               # 'D'
                suffix = 0
                for j in range(n, -1, -1):
                    new_dp[j] = suffix
                    suffix = (suffix + dp[j]) % MOD
            dp = new_dp
        return sum(dp) % MOD