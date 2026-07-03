from typing import List
from collections import deque

class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        M, N = range(m), range(n)
        dir = ((), (0,1), (0,-1), (1,0), (-1,0))  # 1: right, 2: left, 3: down, 4: up
        queue = deque()

        def seen(x: int, y: int) -> bool:
            return x not in M or y not in N or grid[x][y] is None

        def dfs(x: int, y: int) -> None:
            while not seen(x, y):
                dx, dy = dir[grid[x][y]]
                grid[x][y] = None          # mark visited
                queue.append((x, y))
                x, y = x + dx, y + dy

        dfs(0, 0)
        cost = 0
        while queue:
            if (m - 1, n - 1) in queue:
                return cost
            cost += 1
            q = len(queue)
            for _ in range(q):
                x, y = queue.popleft()
                for dx, dy in dir[1:]:
                    dfs(x + dx, y + dy)
        return -1  # per problem constraints this line is never reached