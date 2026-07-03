import collections
from typing import List

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if m * n <= 2:
            return True
        
        dirs = [(-1, 0), (0, -1)]
        def dfs(i: int, j: int) -> None:
            grid[i][j] = 2
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    dfs(ni, nj)
        
        dfs(m - 1, n - 1)
        
        if grid[0][0] != 2:
            return True
        
        dq = collections.deque([(0, 0)])
        grid[0][0] = 0
        dirs = [(1, 0), (0, 1)]
        while dq:
            level_size = len(dq)
            for _ in range(level_size):
                i, j = dq.popleft()
                for di, dj in dirs:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                        dq.append((ni, nj))
                        grid[ni][nj] = 0
            if len(dq) == 1 and dq[0] != (m - 1, n - 1):
                return True
        return False