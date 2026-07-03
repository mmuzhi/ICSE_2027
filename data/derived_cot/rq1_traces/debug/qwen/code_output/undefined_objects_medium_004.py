class Solution:
    def minIncrements(self, n: int, cost: List[int]) -> int:
        minimal = [0] * n
        for i in range(n-1, -1, -1):
            if 2*i+2 < n:
                minimal[i] = max(minimal[2*i+1], minimal[2*i+2])
            else:
                minimal[i] = cost[i]
        ans = 0
        for i in range(n):
            if 2*i+2 < n:
                ans += max(0, minimal[i] - cost[i])
        return ans