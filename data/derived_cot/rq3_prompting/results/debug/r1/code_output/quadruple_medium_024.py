from typing import List
from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        # If start or end is blocked, no path exists
        if grid[0][0] == 0 or grid[m-1][n-1] == 0:
            return True

        # BFS to find one arbitrary path from (0,0) to (m-1,n-1)
        parent = [[None]*n for _ in range(m)]
        q = deque()
        q.append((0, 0))
        parent[0][0] = (0, 0)
        dirs = [(1,0), (-1,0), (0,1), (0,-1)]
        found = False
        while q:
            i, j = q.popleft()
            if i == m-1 and j == n-1:
                found = True
                break
            for di, dj in dirs:
                ni, nj = i+di, j+dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1 and parent[ni][nj] is None:
                    parent[ni][nj] = (i, j)
                    q.append((ni, nj))
        if not found:
            return True  # already no path

        # Reconstruct the path (excluding the start and end)
        path = []
        cur = (m-1, n-1)
        while cur != (0, 0):
            path.append(cur)
            cur = parent[cur[0]][cur[1]]
        # path now contains all cells from end to start, but start is missing

        # Test removal of each interior cell on the path
        for cell in path[1:]:  # exclude end, start will not be tested (start is not in path)
            i, j = cell
            grid[i][j] = 0   # attempt to cut
            # BFS again to see if a path still exists
            visited = [[False]*n for _ in range(m)]
            q2 = deque()
            q2.append((0, 0))
            visited[0][0] = True
            reachable = False
            while q2:
                x, y = q2.popleft()
                if x == m-1 and y == n-1:
                    reachable = True
                    break
                for dx, dy in dirs:
                    nx, ny = x+dx, y+dy
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1 and not visited[nx][ny]:
                        visited[nx][ny] = True
                        q2.append((nx, ny))
            grid[i][j] = 1   # restore
            if not reachable:
                return True
        return False