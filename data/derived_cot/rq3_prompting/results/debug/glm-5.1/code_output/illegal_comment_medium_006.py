from typing import List

class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        M, N = len(grid), len(grid[0])
        res = 0
        
        for i in range(M - 2):
            for j in range(N - 2):
                s = set()
                valid = True
                for x in range(3):
                    for y in range(3):
                        val = grid[i+x][j+y]
                        if val < 1 or val > 9:
                            valid = False
                            break
                        s.add(val)
                    if not valid:
                        break
                
                if not valid or len(s) != 9:
                    continue
                    
                r1 = grid[i][j] + grid[i][j+1] + grid[i][j+2]
                r2 = grid[i+1][j] + grid[i+1][j+1] + grid[i+1][j+2]
                r3 = grid[i+2][j] + grid[i+2][j+1] + grid[i+2][j+2]
                c1 = grid[i][j] + grid[i+1][j] + grid[i+2][j]
                c2 = grid[i][j+1] + grid[i+1][j+1] + grid[i+2][j+1]
                c3 = grid[i][j+2] + grid[i+1][j+2] + grid[i+2][j+2]
                d1 = grid[i][j] + grid[i+1][j+1] + grid[i+2][j+2]
                d2 = grid[i+2][j] + grid[i+1][j+1] + grid[i][j+2]
                
                if r1 == r2 == r3 == c1 == c2 == c3 == d1 == d2 == 15:
                    res += 1
        
        return res