class Solution:
    def maxDistance(self, colors: List[int]) -> int:
        ans = 0
        n = len(colors)
        for i, x in enumerate(colors):
            if x != colors[0]:
                ans = max(ans, i)
            if x != colors[-1]:
                ans = max(ans, n - 1 - i)
        return ans