from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if not self.bfs(grid, 0, 0, m-1, n-1):
            return True
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    grid[i][j] = 0
                    if not self.bfs(grid, 0, 0, m-1, n-1):
                        return True
                    grid[i][j] = 1
        return False

    def bfs(self, grid, sr, sc, er, ec):
        m, n = len(grid), len(grid[0])
        dq = deque()
        dq.append((sr, sc))
        visited = [[False] * n for _ in range(m)]
        visited[sr][sc] = True
        while dq:
            x, y = dq.popleft()
            if x == er and y == ec:
                return True
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny] and grid[nx][ny] == 1:
                    visited[nx][ny] = True
                    dq.append((nx, ny))
        return False