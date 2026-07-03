import heapq
from typing import List

class Solution:
    def minimumObstacles(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        distance = [[float('inf')] * n for _ in range(m)]
        distance[0][0] = grid[0][0]
        q = []
        heapq.heappush(q, (distance[0][0], 0, 0))
        
        while q:
            d, i, j = heapq.heappop(q)
            if d != distance[i][j]:
                continue
            if i == m-1 and j == n-1:
                return d
            for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                ci, cj = i + di, j + dj
                if 0 <= ci < m and 0 <= cj < n:
                    new_cost = d + grid[ci][cj]
                    if new_cost < distance[ci][cj]:
                        distance[ci][cj] = new_cost
                        heapq.heappush(q, (new_cost, ci, cj))
        return distance[m-1][n-1]