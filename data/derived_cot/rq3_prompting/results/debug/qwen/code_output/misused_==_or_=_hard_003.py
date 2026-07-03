class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        grid = [[1 if ch == 'A' else 0 for ch in row] for row in pizza]
        
        self.pref = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(1, self.r + 1):
            for j in range(1, self.c + 1):
                self.pref[i][j] = grid[i-1][j-1] + self.pref[i-1][j] + self.pref[i][j-1] - self.pref[i-1][j-1]
        
        tot_apples = self.pref[self.r][self.c]
        if tot_apples < k:
            return 0
        
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def getAppleCount(i1, i2, j1, j2):
            if i1 > i2 or j1 > j2:
                return 0
            return self.pref[i2+1][j2+1] - self.pref[i1][j2+1] - self.pref[i2+1][j1] + self.pref[i1][j1]
        
        @lru_cache(maxsize=None)
        def getWays(i, j, k):
            if k == 1:
                return 1 if getAppleCount(i, self.r-1, j, self.c-1) > 0 else 0
            
            total_ways = 0
            
            # Horizontal cuts
            for nr in range(i, self.r - 1):
                if getAppleCount(i, nr, j, self.c-1) > 0 and getAppleCount(nr+1, self.r-1, j, self.c-1) > 0:
                    total_ways += getWays(i, j, 1) * getWays(nr+1, j, k-1)
            
            # Vertical cuts
            for nc in range(j, self.c - 1):
                if getAppleCount(i, self.r-1, j, nc) > 0 and getAppleCount(i, self.r-1, nc+1, self.c-1) > 0:
                    total_ways += getWays(i, j, 1) * getWays(i, nc+1, k-1)
            
            return total_ways % (10**9 + 7)
        
        return getWays(0, 0, k)