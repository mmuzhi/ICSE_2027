from typing import List
import collections

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        # Reverse directions: up and left
        dirs_rev = [(-1, 0), (0, -1)]

        # DFS to mark all cells that can reach (m-1, n-1) using reverse moves
        def dfs(i: int, j: int) -> None:
            grid[i][j] = 2
            for di, dj in dirs_rev:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    dfs(ni, nj)

        # Start marking from bottom-right if it is passable
        if grid[m-1][n-1] == 1:
            dfs(m-1, n-1)

        # BFS from top-left moving down/right, only on cells marked 2
        dq = collections.deque([(0, 0)])
        grid[0][0] = 0  # mark start as visited
        dirs = [(1, 0), (0, 1)]

        while dq:
            level_size = len(dq)
            # If only one cell at current level (and it's not start or end), cut is possible
            if level_size == 1:
                cell = dq[0]
                if cell != (0, 0) and cell != (m-1, n-1):
                    return True
            for _ in range(level_size):
                i, j = dq.popleft()
                if i == m-1 and j == n-1:
                    return False
                for di, dj in dirs:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                        dq.append((ni, nj))
                        grid[ni][nj] = 0

        # No path from start to end → cut is possible (trivially)
        return True