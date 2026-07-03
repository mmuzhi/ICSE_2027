class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9 + 7
        dp = [1]  # permutations of length 1 (the first element)

        for ch in s:
            new_dp = [0] * (len(dp) + 1)
            if ch == 'I':
                cum = 0
                for j in range(len(new_dp)):
                    new_dp[j] = cum
                    if j < len(dp):
                        cum = (cum + dp[j]) % MOD
            else:  # 'D'
                cum = 0
                for j in range(len(new_dp) - 1, -1, -1):
                    new_dp[j] = cum
                    if j - 1 >= 0:
                        cum = (cum + dp[j - 1]) % MOD
            dp = new_dp

        return sum(dp) % MOD