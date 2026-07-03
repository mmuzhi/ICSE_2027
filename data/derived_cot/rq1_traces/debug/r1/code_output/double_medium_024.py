class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        MOD1 = 10**9 + 7
        MOD2 = 10**9 + 9
        m, n = len(grid), len(grid[0])
        if grid[0][0] == 0 or grid[m-1][n-1] == 0:
            return True
        
        dp1_1 = [[0] * n for _ in range(m)]
        dp1_2 = [[0] * n for _ in range(m)]
        dp1_1[0][0] = 1
        dp1_2[0][0] = 1
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0:
                    continue
                if i > 0:
                    dp1_1[i][j] = (dp1_1[i][j] + dp1_1[i-1][j]) % MOD1
                    dp1_2[i][j] = (dp1_2[i][j] + dp1_2[i-1][j]) % MOD2
                if j > 0:
                    dp1_1[i][j] = (dp1_1[i][j] + dp1_1[i][j-1]) % MOD1
                    dp1_2[i][j] = (dp1_2[i][j] + dp1_2[i][j-1]) % MOD2
        
        total1 = dp1_1[m-1][n-1]
        total2 = dp1_2[m-1][n-1]
        if total1 == 0 or total2 == 0:
            return True
        
        dp2_1 = [[0] * n for _ in range(m)]
        dp2_2 = [[0] * n for _ in range(m)]
        dp2_1[m-1][n-1] = 1
        dp2_2[m-1][n-1] = 1
        for i in range(m-1, -1, -1):
            for j in range(n-1, -1, -1):
                if grid[i][j] == 0:
                    continue
                if i < m-1:
                    dp2_1[i][j] = (dp2_1[i][j] + dp2_1[i+1][j]) % MOD1
                    dp2_2[i][j] = (dp2_2[i][j] + dp2_2[i+1][j]) % MOD2
                if j < n-1:
                    dp2_1[i][j] = (dp2_1[i][j] + dp2_1[i][j+1]) % MOD1
                    dp2_2[i][j] = (dp2_2[i][j] + dp2_2[i][j+1]) % MOD2
        
        for i in range(m):
            for j in range(n):
                if (i == 0 and j == 0) or (i == m-1 and j == n-1):
                    continue
                if grid[i][j] == 1:
                    prod1 = (dp1_1[i][j] * dp2_1[i][j]) % MOD1
                    prod2 = (dp1_2[i][j] * dp2_2[i][j]) % MOD2
                    if prod1 == total1 and prod2 == total2:
                        return True
        return False