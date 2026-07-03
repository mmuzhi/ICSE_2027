class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9+7
        dp = [1]  # number of permutations of length 1
        for ch in s:
            L = len(dp)
            new = [0] * (L+1)
            if ch == 'I':
                total = 0
                for j in range(1, L+1):
                    total = (total + dp[j-1]) % MOD
                    new[j] = total
            else:  # 'D'
                total = 0
                for j in range(L-1, -1, -1):
                    total = (total + dp[j]) % MOD
                    new[j] = total
            dp = new
        return sum(dp) % MOD