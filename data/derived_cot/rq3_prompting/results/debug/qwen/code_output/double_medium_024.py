class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if grid[0][0] == 0 or grid[m-1][n-1] == 0:
            return True
        if m == 1 and n == 1:
            return False
        if (m == 1 and n == 2) or (m == 2 and n == 1):
            return False
        return True