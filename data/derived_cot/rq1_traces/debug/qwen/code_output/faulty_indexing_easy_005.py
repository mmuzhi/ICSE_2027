class Solution:
    def deleteGreatestValue(self, grid: List[List[int]]) -> int:
        for i in range(len(grid)):
            grid[i].sort()
        n = len(grid[0])
        res = 0
        for j in range(n):
            ans = 0
            for i in range(len(grid)):
                if len(grid[i]) > j:
                    ans = max(ans, grid[i].pop(-(j+1)))
            res += ans
        return res