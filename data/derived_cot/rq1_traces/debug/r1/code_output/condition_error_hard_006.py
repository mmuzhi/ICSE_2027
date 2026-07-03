from collections import deque
from typing import List

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        M, N = range(m), range(n)
        directions = ((), (0, 1), (0, -1), (1, 0), (-1, 0))
        queue = deque()
        
        seen = lambda x, y: x not in M or y not in N or not grid[x][y]
        
        def dfs(x: int, y: int) -> None:
            while not seen(x, y):
                dx, dy = directions[grid[x][y]]
                grid[x][y] = None  # Mark as visited
                queue.append((x, y))
                x, y = x + dx, y + dy
        
        dfs(0, 0)
        if (m-1, n-1) in queue:
            return 0
        
        cost = 0
        while queue:
            cost += 1
            level_size = len(queue)
            for _ in range(level_size):
                x, y = queue.popleft()
                for dx, dy in directions[1:]:  # Explore all four directions
                    dfs(x + dx, y + dy)
            if (m-1, n-1) in queue:
                return cost
        
        return -1