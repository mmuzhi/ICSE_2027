class Solution:
    def minCost(self, A, K):
        n = len(A)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        for i in range(n):
            C = [0] * (n + 1)
            val = 0
            for j in range(i, -1, -1):
                color = A[j]
                if C[color] == 0:
                    pass
                else:
                    val += 1
                C[color] += 1
                if dp[j] + val < dp[i + 1]:
                    dp[i + 1] = dp[j] + val
        return dp[n]