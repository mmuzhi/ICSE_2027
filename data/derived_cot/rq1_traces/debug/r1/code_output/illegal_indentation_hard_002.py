from collections import deque
from typing import List

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        cost = 0
        queue = deque()
        dirs = ((), (0, 1), (0, -1), (1, 0), (-1, 0))
        
        seen = lambda x, y: not (0 <= x < m and 0 <= y < n) or grid[x][y] is None
        
        def dfs(x, y):
            while not seen(x, y):
                dx, dy = dirs[grid[x][y]]
                grid[x][y] = None
                queue.append((x, y))
                x, y = x + dx, y + dy
        
        dfs(0, 0)
        
        while queue:
            if grid[m-1][n-1] is None:
                return cost
            cost += 1
            q_len = len(queue)
            for _ in range(q_len):
                x, y = queue.popleft()
                for dx, dy in dirs[1:]:
                    dfs(x + dx, y + dy)
        
        return cost