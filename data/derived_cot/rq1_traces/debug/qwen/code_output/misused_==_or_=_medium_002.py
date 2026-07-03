from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if grid[m-1][n-1] == 0:
            return False
        
        dp = [[0] * n for _ in range(m)]
        dp[0][0] = 1
        dq = deque([(0, 0)])
        
        while dq:
            i, j = dq.popleft()
            if dp[i][j] >= 2:
                return True
            if i == m-1 and j == n-1:
                continue
            for di, dj in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    if dp[ni][nj] < 2:
                        dp[ni][nj] += dp[i][j]
                        if dp[ni][nj] >= 2:
                            return True
                        dq.append((ni, nj))
        return False