import collections

class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        if grid[0][0] == 0 or grid[m-1][n-1] == 0:
            return True
        
        dq_dest = collections.deque()
        dq_dest.append((m-1, n-1))
        grid[m-1][n-1] = 2
        dirs_dest = [(-1, 0), (0, -1)]
        while dq_dest:
            i, j = dq_dest.popleft()
            for di, dj in dirs_dest:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 1:
                    grid[ni][nj] = 2
                    dq_dest.append((ni, nj))
        
        dq = collections.deque()
        dq.append((0, 0))
        grid[0][0] = 0
        dirs = [(1, 0), (0, 1)]
        found = False
        while dq:
            i, j = dq.popleft()
            if i == m-1 and j == n-1:
                found = True
                break
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and grid[ni][nj] == 2:
                    dq.append((ni, nj))
        
        if found:
            return False
        
        if len(dq) == 1 and dq[0] != (m-1, n-1):
            return True
        
        return True