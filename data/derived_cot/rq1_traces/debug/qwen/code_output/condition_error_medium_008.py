class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        n = len(grid[0])
        if n == 1:
            return grid[0][0]
        if n == 2:
            return min(max(grid[0]), max(grid[1]))
        else:
            return min(max(grid[0][0], grid[0][1]), max(grid[1][1:]), max(grid[0][1:], grid[1][0]))