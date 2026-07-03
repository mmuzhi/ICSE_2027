class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9 + 7
        n = len(s)
        # dp[i][j] = number of permutations of length i+1 ending with j
        dp = [[0] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 1

        for i, ch in enumerate(s):
            # Build prefix sums of dp[i] for fast range queries
            prefix = [0] * (n + 2)
            for j in range(n + 1):
                prefix[j + 1] = (prefix[j] + dp[i][j]) % MOD

            # Compute dp[i+1][j] for all possible j (0 .. i+1)
            for j in range(i + 2):
                if ch == 'I':
                    # Sum over k < j
                    dp[i + 1][j] = prefix[j]
                else:  # 'D'
                    # Sum over k >= j
                    dp[i + 1][j] = (prefix[i + 2] - prefix[j]) % MOD

        return sum(dp[n][j] for j in range(n + 1)) % MOD