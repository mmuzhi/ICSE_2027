from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        dirs_rev = [(-1, 0), (0, -1)]
        dq_rev = deque()
        dq_rev.append((m-1, n-1))
        grid[m-1][n-1] = 2
        while dq_rev:
            i, j = dq_rev.popleft()
            for di, dj in dirs_rev:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    grid[ni][nj] = 2
                    dq_rev.append((ni, nj))
        
        dq = deque()
        if grid[0][0] == 2:
            dq.append((0, 0))
            grid[0][0] = 0
        while dq:
            i, j = dq.popleft()
            if i == m-1 and j == n-1:
                return True
            for di, dj in [(0, 1), (1, 0)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                    dq.append((ni, nj))
                    grid[ni][nj] = 0
        return False