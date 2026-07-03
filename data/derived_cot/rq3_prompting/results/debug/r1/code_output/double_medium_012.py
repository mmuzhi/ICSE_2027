from typing import List
from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        # Reverse DFS: mark all cells that can reach bottom-right by moving up/left
        dirs_rev = [(-1, 0), (0, -1)]
        def dfs(i: int, j: int) -> None:
            grid[i][j] = 2
            for di, dj in dirs_rev:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    dfs(ni, nj)

        dfs(m - 1, n - 1)

        # BFS from top-left to bottom-right, only on cells marked 2
        dq = deque([(0, 0)])
        grid[0][0] = 0
        dirs_fwd = [(1, 0), (0, 1)]
        while dq:
            l = len(dq)
            for _ in range(l):
                i, j = dq.popleft()
                if i == m - 1 and j == n - 1:
                    return False  # reached the end without a bottleneck
                for di, dj in dirs_fwd:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                        dq.append((ni, nj))
                        grid[ni][nj] = 0
            # After processing a level, check for a single cell on the frontier
            if len(dq) == 1 and dq[0] != (m - 1, n - 1):
                return True

        # No path exists at all -> already cut
        return True