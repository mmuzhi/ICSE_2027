from collections import deque

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        if m == 0 or n == 0:
            return 0
        
        dir = ((), (0,1), (0,-1), (1,0), (-1,0))
        
        visited = [[False] * n for _ in range(m)]
        queue = deque()
        queue.append((0, 0))
        visited[0][0] = True
        cost = 0
        
        while queue:
            size = len(queue)
            for _ in range(size):
                x, y = queue.popleft()
                if x == m-1 and y == n-1:
                    return cost
                d = grid[x][y]
                if d == 0:
                    continue
                dx, dy = dir[d]
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny]:
                    visited[nx][ny] = True
                    queue.append((nx, ny))
            cost += 1
        
        return cost