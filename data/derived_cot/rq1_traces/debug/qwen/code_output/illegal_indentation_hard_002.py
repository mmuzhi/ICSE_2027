from collections import deque
from typing import List

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        if grid[0][0] == 0:
            return 0 if (0,0) == (m-1, n-1) else float('inf')
        
        directions = {
            1: (0, 1),
            2: (0, -1),
            3: (1, 0),
            4: (-1, 0)
        }
        
        queue = deque()
        queue.append((0, 0))
        visited = [[False] * n for _ in range(m)]
        visited[0][0] = True
        cost = 0
        
        while queue:
            if queue[0] == (m-1, n-1):
                return cost
            cost += 1
            size = len(queue)
            for _ in range(size):
                x, y = queue.popleft()
                if grid[x][y] == 0:
                    continue
                dx, dy = directions[grid[x][y]]
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny]:
                    visited[nx][ny] = True
                    queue.append((nx, ny))
        return -1