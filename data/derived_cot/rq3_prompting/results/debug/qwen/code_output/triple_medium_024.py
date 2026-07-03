import collections

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if grid[0][0] == 0 or grid[m-1][n-1] == 0:
            return True
        
        dirs = [(1, 0), (0, 1)]
        dq = collections.deque()
        visited = [[False] * n for _ in range(m)]
        visited[0][0] = True
        dq.append((0, 0))
        
        while dq:
            i, j = dq.popleft()
            if i == m-1 and j == n-1:
                return False
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and not visited[ni][nj] and grid[ni][nj] == 1:
                    visited[ni][nj] = True
                    dq.append((ni, nj))
        
        return True