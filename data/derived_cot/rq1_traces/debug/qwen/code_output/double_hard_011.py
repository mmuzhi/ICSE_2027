import heapq
from typing import List

class Solution:
    def minimumObstacles(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        distance = [[float('inf')] * n for _ in range(m)]
        distance[0][0] = 0
        
        heap = [(0, 0, 0)]
        
        while heap:
            d, i, j = heapq.heappop(heap)
            if i == m - 1 and j == n - 1:
                return d
            if d > distance[i][j]:
                continue
            for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n:
                    new_cost = d + grid[ni][nj]
                    if new_cost < distance[ni][nj]:
                        distance[ni][nj] = new_cost
                        heapq.heappush(heap, (new_cost, ni, nj))
        return distance[m-1][n-1]