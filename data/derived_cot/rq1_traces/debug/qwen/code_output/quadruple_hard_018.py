from collections import deque

class Solution:
    def minimumObstacles(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        dist = [[float('inf')] * n for _ in range(m)]
        dist[0][0] = 0
        q = deque([(0, 0)])
        
        while q:
            i, j = q.popleft()
            if i == m-1 and j == n-1:
                return dist[i][j]
            for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n:
                    new_cost = dist[i][j] + grid[ni][nj]
                    if new_cost < dist[ni][nj]:
                        dist[ni][nj] = new_cost
                        if grid[ni][nj] == 0:
                            q.appendleft((ni, nj))
                        else:
                            q.append((ni, nj))
        return dist[m-1][n-1]