import collections
from typing import List

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        dirs = [(-1, 0), (0, -1)]  # Directions for DFS (up, left)
        
        def dfs(i: int, j: int) -> None:
            if grid[i][j] != 1:
                return
            grid[i][j] = 2
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n:
                    dfs(ni, nj)
        
        # Perform DFS from the end to mark reachable paths
        dfs(m - 1, n - 1)
        
        # If start is not reachable from end, return True
        if grid[0][0] != 2:
            return True
        
        # BFS from start to end to check for critical nodes
        dq = collections.deque([(0, 0)])
        grid[0][0] = 0  # Mark as visited
        dirs = [(1, 0), (0, 1)]  # Directions for BFS (down, right)
        
        while dq:
            level_size = len(dq)
            # Check if current level has exactly one node and it's not the end
            if level_size == 1:
                (x, y) = dq[0]
                if (x, y) != (m - 1, n - 1):
                    return True
            for _ in range(level_size):
                i, j = dq.popleft()
                for di, dj in dirs:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                        grid[ni][nj] = 0  # Mark as visited
                        dq.append((ni, nj))
        
        return False