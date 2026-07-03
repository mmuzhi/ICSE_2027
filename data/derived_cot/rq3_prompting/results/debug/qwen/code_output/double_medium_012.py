import collections

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        dirs = [(-1, 0), (0, -1)]
        
        def dfs(i: int, j: int) -> None:
            grid[i][j] = 2
        
        for di, dj in dirs:
            if 0 <= i + di < m and 0 <= j + dj < n and grid[i + di][j + dj] == 1:
                dfs(i + di, j + dj)
        
        dfs(m - 1, n - 1)
        
        dq = collections.deque([(0, 0)])
        grid[0][0] = 0
        dirs = [(1, 0), (0, 1)]
        while dq:
            l = len(dq)
            for _ in range(l):
                i, j = dq.popleft()
                if i == m - 1 and j == n - 1:
                    return False
                for di, dj in dirs:
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] != 2 and grid[ni][nj] != 0:
                        dq.append((ni, nj))
            if len(dq) == 1 and dq[0] != (m - 1, n - 1):
                return True
        
        return True