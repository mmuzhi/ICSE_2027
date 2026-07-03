from typing import List
from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 10**9 + 7
        self.r = len(pizza)
        self.c = len(pizza[0])
        
        # Precompute 2D prefix sum of apples
        self.preSum = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r):
            for j in range(self.c):
                self.preSum[i+1][j+1] = self.preSum[i][j+1] + self.preSum[i+1][j] - self.preSum[i][j]
                if pizza[i][j] == 'A':
                    self.preSum[i+1][j+1] += 1
        
        total_apples = self.preSum[self.r][self.c]
        if total_apples < k:
            return 0
        if k == 1:
            return 1
        
        return self.getWays(0, 0, k) % MOD
    
    @cache
    def getWays(self, i: int, j: int, k: int) -> int:
        MOD = 10**9 + 7
        if k == 1:
            # Check if the current piece has at least one apple
            sum_region = self.preSum[self.r][self.c] - self.preSum[i][self.c] - self.preSum[self.r][j] + self.preSum[i][j]
            return 1 if sum_region >= 1 else 0
        
        res = 0
        # Try all horizontal cuts
        for nr in range(i, self.r - 1):
            # Check if the upper part (i to nr, j to c-1) has at least one apple
            sum_upper = self.preSum[nr+1][self.c] - self.preSum[i][self.c] - self.preSum[nr+1][j] + self.preSum[i][j]
            if sum_upper >= 1:
                res += self.getWays(nr + 1, j, k - 1)
                res %= MOD
        
        # Try all vertical cuts
        for nc in range(j, self.c - 1):
            # Check if the left part (i to r-1, j to nc) has at least one apple
            sum_left = self.preSum[self.r][nc+1] - self.preSum[i][nc+1] - self.preSum[self.r][j] + self.preSum[i][j]
            if sum_left >= 1:
                res += self.getWays(i, nc + 1, k - 1)
                res %= MOD
        
        return res % MOD