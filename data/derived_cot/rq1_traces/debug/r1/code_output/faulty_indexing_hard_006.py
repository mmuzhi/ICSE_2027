from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        
        self.pre = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r):
            for j in range(self.c):
                self.pre[i + 1][j + 1] = (1 if pizza[i][j] == 'A' else 0) + self.pre[i][j + 1] + self.pre[i + 1][j] - self.pre[i][j]
        
        tot_apples = self.pre[self.r][self.c]
        if tot_apples < k:
            return 0
        if k == 1:
            return 1
        
        return self.getWays(0, 0, k - 1) % 1000000007
    
    @lru_cache(maxsize=None)
    def getWays(self, i: int, j: int, k: int) -> int:
        if k == 0:
            apples_here = self.pre[self.r][self.c] - self.pre[i][self.c] - self.pre[self.r][j] + self.pre[i][j]
            return 1 if apples_here > 0 else 0
        
        total_ways = 0
        mod = 1000000007
        
        for nr in range(i, self.r - 1):
            apples_top = self.pre[nr + 1][self.c] - self.pre[i][self.c] - self.pre[nr + 1][j] + self.pre[i][j]
            if apples_top > 0:
                total_ways = (total_ways + self.getWays(nr + 1, j, k - 1)) % mod
        
        for nc in range(j, self.c - 1):
            apples_left = self.pre[self.r][nc + 1] - self.pre[i][nc + 1] - self.pre[self.r][j] + self.pre[i][j]
            if apples_left > 0:
                total_ways = (total_ways + self.getWays(i, nc + 1, k - 1)) % mod
        
        return total_ways