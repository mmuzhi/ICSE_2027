from collections import deque

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        dir = ((), (0,1), (0,-1), (1,0), (-1,0))
        visited = [[False] * n for _ in range(m)]
        queue = deque()
        visited[0][0] = True
        queue.append((0,0))
        cost = 1

        while queue:
            x, y = queue.popleft()
            if x == m-1 and y == n-1:
                return cost
            val = grid[x][y]
            dx, dy = dir[val]
            nx, ny = x + dx, y + dy
            if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny] and grid[nx][ny] != 0:
                visited[nx][ny] = True
                cost += 1
                queue.append((nx, ny))
        return cost