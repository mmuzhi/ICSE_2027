from typing import List
from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        dirs = [(-1, 0), (0, -1)]
        
        def dfs(i: int, j: int) -> None:
            grid[i][j] = 2
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    dfs(ni, nj)
        
        dfs(m - 1, n - 1)
        
        if grid[0][0] != 2:
            return False
        
        dq = deque([(0, 0)])
        grid[0][0] = 0
        dirs = [(1, 0), (0, 1)]
        
        while dq:
            level_size = len(dq)
            # Check if current level has exactly one cell (a potential bottleneck)
            if level_size == 1:
                i, j = dq[0]
                if (i, j) != (0, 0) and (i, j) != (m - 1, n - 1):
                    return True
            for _ in range(level_size):
                i, j = dq.popleft()
                for di, dj in dirs:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                        dq.append((ni, nj))
                        grid[ni][nj] = 0
        
        return False