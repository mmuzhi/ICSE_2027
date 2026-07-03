from typing import List
import collections

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        dirs = [(-1, 0), (0, -1)]
        
        def dfs(i: int, j: int) -> None:
            if i < 0 or i >= m or j < 0 or j >= n or grid[i][j] != 1:
                return
            grid[i][j] = 2
            for di, dj in dirs:
                dfs(i + di, j + dj)
        
        # Perform DFS from the end to mark reachable cells
        if grid[m-1][n-1] == 0:
            return True
        dfs(m-1, n-1)
        if grid[0][0] != 2:
            return True
        
        # BFS from start to check for bottlenecks
        dq = collections.deque([(0, 0)])
        grid[0][0] = 0
        bfs_dirs = [(1, 0), (0, 1)]
        
        while dq:
            level_size = len(dq)
            if level_size == 1:
                x, y = dq[0]
                if (x, y) != (m-1, n-1):
                    return True
            for _ in range(level_size):
                i, j = dq.popleft()
                for di, dj in bfs_dirs:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                        grid[ni][nj] = 0
                        dq.append((ni, nj))
                        if ni == m-1 and nj == n-1:
                            return False
        return True