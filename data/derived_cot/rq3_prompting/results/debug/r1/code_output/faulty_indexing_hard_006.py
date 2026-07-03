from typing import List
from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 1000000007
        self.r = len(pizza)
        self.c = len(pizza[0])
        
        # Build 2D prefix sum of apples (1-indexed)
        self.pref = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(1, self.r + 1):
            row_sum = 0
            for j in range(1, self.c + 1):
                if pizza[i-1][j-1] == 'A':
                    row_sum += 1
                self.pref[i][j] = self.pref[i-1][j] + row_sum
        
        # Helper to count apples in rectangle (r1,c1) inclusive to (r2,c2) inclusive
        def apples(r1: int, c1: int, r2: int, c2: int) -> int:
            return (self.pref[r2+1][c2+1] - self.pref[r1][c2+1] -
                    self.pref[r2+1][c1] + self.pref[r1][c1])
        
        # Check if there are enough apples for k pieces
        if apples(0, 0, self.r-1, self.c-1) < k:
            return 0
        
        @lru_cache(None)
        def dfs(i: int, j: int, pieces: int) -> int:
            if pieces == 1:
                return 1 if apples(i, j, self.r-1, self.c-1) > 0 else 0
            
            total = 0
            # Horizontal cuts
            for r in range(i, self.r-1):
                if apples(i, j, r, self.c-1) > 0:
                    total += dfs(r+1, j, pieces-1)
            # Vertical cuts
            for c in range(j, self.c-1):
                if apples(i, j, self.r-1, c) > 0:
                    total += dfs(i, c+1, pieces-1)
            return total % MOD
        
        return dfs(0, 0, k) % MOD