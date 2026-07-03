from typing import List

class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        M, N = len(grid), len(grid[0])
        res = 0
        for i in range(M - 2):
            for j in range(N - 2):
                # check distinct numbers 1-9
                vals = []
                for r in range(3):
                    for c in range(3):
                        vals.append(grid[i + r][j + c])
                if sorted(vals) != list(range(1, 10)):
                    continue
                # check row, column, diagonal sums
                if (grid[i][j] + grid[i][j+1] + grid[i][j+2] != 15 or
                    grid[i+1][j] + grid[i+1][j+1] + grid[i+1][j+2] != 15 or
                    grid[i+2][j] + grid[i+2][j+1] + grid[i+2][j+2] != 15 or
                    grid[i][j] + grid[i+1][j] + grid[i+2][j] != 15 or
                    grid[i][j+1] + grid[i+1][j+1] + grid[i+2][j+1] != 15 or
                    grid[i][j+2] + grid[i+1][j+2] + grid[i+2][j+2] != 15 or
                    grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2] != 15 or
                    grid[i][j+2] + grid[i+1][j+1] + grid[i+2][j] != 15):
                    continue
                res += 1
        return res