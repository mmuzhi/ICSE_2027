from collections import deque

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if m == 0 or n == 0:
            return False
        
        if grid[0][0] == 1:
            has_adj = False
            for di, dj in [(-1,0), (0,-1), (1,0), (0,1)]:
                ni, nj = 0 + di, 0 + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 0:
                    has_adj = True
                    break
            if not has_adj:
                return False
            else:
                grid[0][0] = 0
        
        visited = [[False] * n for _ in range(m)]
        dq = deque()
        dq.append((0, 0))
        visited[0][0] = True
        
        while dq:
            i, j = dq.popleft()
            if i == m-1 and j == n-1:
                return True
            
            for di, dj in [(-1,0), (0,-1), (1,0), (0,1)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and not visited[ni][nj]:
                    if grid[ni][nj] == 1:
                        has_adj = False
                        for d in [(-1,0), (0,-1), (1,0), (0,1)]:
                            x, y = ni + d[0], nj + d[1]
                            if 0 <= x < m and 0 <= y < n and grid[x][y] == 0:
                                has_adj = True
                                break
                        if has_adj:
                            grid[ni][nj] = 0
                            visited[ni][nj] = True
                            dq.append((ni, nj))
                    else:
                        visited[ni][nj] = True
                        dq.append((ni, nj))
        
        return False