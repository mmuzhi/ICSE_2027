class Solution:
    def minCost(self, A, K):
        n = len(A)
        dp = [0] + [float('inf')] * n
        for i in range(n):
            C = {}
            distinct = 0
            for j in range(i, -1, -1):
                if A[j] not in C:
                    C[A[j]] = 0
                    distinct += 1
                C[A[j]] += 1
                if distinct >= K:
                    dp[i+1] = min(dp[i+1], dp[j] + (i - j + 1))
                    break
        return dp[-1]