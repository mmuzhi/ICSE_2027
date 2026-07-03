from typing import List
from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        
        # Precompute the 2D prefix sum of apples
        self.prefix = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        tot_apples = 0
        for i in range(self.r):
            for j in range(self.c):
                current = 1 if pizza[i][j] == 'A' else 0
                tot_apples += current
                self.prefix[i+1][j+1] = current + self.prefix[i][j+1] + self.prefix[i+1][j] - self.prefix[i][j]
        
        if tot_apples < k:
            return 0
        if k == 1:
            return 1
        
        return self.getWays(0, 0, k) % (10**9 + 7)
    
    @cache
    def getWays(self, i: int, j: int, k: int) -> int:
        if k == 1:
            # Check if the current region has at least one apple
            total = self.prefix[self.r][self.c] - self.prefix[i][self.c] - self.prefix[self.r][j] + self.prefix[i][j]
            return 1 if total > 0 else 0
        
        count = 0
        # Try all horizontal cuts
        for nr in range(i, self.r - 1):
            # Check upper piece (i, j) to (nr, c-1)
            sum_upper = self.prefix[nr+1][self.c] - self.prefix[i][self.c] - self.prefix[nr+1][j] + self.prefix[i][j]
            if sum_upper > 0:
                count += self.getWays(nr + 1, j, k - 1)
        
        # Try all vertical cuts
        for nc in range(j, self.c - 1):
            # Check left piece (i, j) to (r-1, nc)
            sum_left = self.prefix[self.r][nc+1] - self.prefix[i][nc+1] - self.prefix[self.r][j] + self.prefix[i][j]
            if sum_left > 0:
                count += self.getWays(i, nc + 1, k - 1)
        
        return count