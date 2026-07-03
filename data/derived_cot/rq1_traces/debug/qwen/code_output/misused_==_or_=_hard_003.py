class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        grid = [[0] * self.c for _ in range(self.r)]
        for i in range(self.r):
            for j in range(self.c):
                if pizza[i][j] == 'A':
                    grid[i][j] = 1
        
        pre = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r):
            for j in range(self.c):
                pre[i+1][j+1] = pre[i+1][j] + pre[i][j+1] - pre[i][j] + grid[i][j]
        
        def getAppleCount(i1, j1, i2, j2):
            if i1 > i2 or j1 > j2:
                return 0
            return pre[i2+1][j2+1] - pre[i1][j2+1] - pre[i2+1][j1] + pre[i1][j1]
        
        from functools import lru_cache
        @lru_cache(maxsize=None)
        def dfs(i, j, x, y, k_val):
            if k_val < 0:
                return 0
            if k_val == 0:
                return 1 if getAppleCount(i, j, x, y) > 0 else 0
            
            ways = 0
            
            for r in range(i+1, x+1):
                if getAppleCount(i, j, r-1, y) > 0 and getAppleCount(r, j, x, y) > 0:
                    for a in range(0, k_val):
                        b = k_val - 1 - a
                        ways += dfs(i, j, r-1, y, a) * dfs(r, j, x, y, b)
            
            for c in range(j+1, y+1):
                if getAppleCount(i, j, x, c-1) > 0 and getAppleCount(i, c, x, y) > 0:
                    for a in range(0, k_val):
                        b = k_val - 1 - a
                        ways += dfs(i, j, x, c-1, a) * dfs(i, c, x, y, b)
            
            return ways
        
        result = dfs(0, 0, self.r-1, self.c-1, k) % (1000000007)
        return result