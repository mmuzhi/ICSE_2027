from typing import List
from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 1000000007
        rows = len(pizza)
        cols = len(pizza[0])
        
        # Build 2D prefix sum: pref[i][j] = apples in rectangle (0,0) to (i-1,j-1)
        pref = [[0] * (cols + 1) for _ in range(rows + 1)]
        total_apples = 0
        for i in range(rows):
            for j in range(cols):
                pref[i+1][j+1] = pref[i][j+1] + pref[i+1][j] - pref[i][j] + (1 if pizza[i][j] == 'A' else 0)
                if pizza[i][j] == 'A':
                    total_apples += 1
        
        if total_apples < k:
            return 0
        if k == 1:
            return 1
        
        @lru_cache(None)
        def getWays(i: int, j: int, k: int) -> int:
            # Returns number of ways to cut submatrix (i,j) to (rows-1,cols-1) into k pieces
            if k == 1:
                apples = pref[rows][cols] - pref[i][cols] - pref[rows][j] + pref[i][j]
                return 1 if apples > 0 else 0
            
            ways = 0
            # Horizontal cuts
            for nr in range(i, rows - 1):
                top_apples = pref[nr+1][cols] - pref[i][cols] - pref[nr+1][j] + pref[i][j]
                if top_apples > 0:
                    ways += getWays(nr + 1, j, k - 1)
            # Vertical cuts
            for nc in range(j, cols - 1):
                left_apples = pref[rows][nc+1] - pref[i][nc+1] - pref[rows][j] + pref[i][j]
                if left_apples > 0:
                    ways += getWays(i, nc + 1, k - 1)
            return ways % MOD
        
        return getWays(0, 0, k) % MOD