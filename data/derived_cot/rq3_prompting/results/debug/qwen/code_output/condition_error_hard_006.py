from collections import deque

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        q = deque()
        q.append((0, 0))
        grid[0][0] = None
        cost = 0
        dir = ((), (0, 1), (0, -1), (1, 0), (-1, 0))
        
        while q:
            size = len(q)
            for _ in range(size):
                x, y = q.popleft()
                if x == m-1 and y == n-1:
                    return cost
                val = grid[x][y]
                dx, dy = dir[val]
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] is not None:
                    grid[nx][ny] = None
                    q.append((nx, ny))
            cost += 1
        
        return cost