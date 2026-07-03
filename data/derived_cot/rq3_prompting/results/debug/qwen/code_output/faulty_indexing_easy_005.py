class Solution:
    def deleteGreatestValue(self, grid: List[List[int]]) -> int:
        for i in range(len(grid)):
            grid[i].sort(reverse=True)
        n = len(grid[0])
        res = 0
        for j in range(n):
            current_max = 0
            for i in range(len(grid)):
                current_max = max(current_max, grid[i][j])
            res += current_max
        return res