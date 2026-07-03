from typing import List
from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 1000000007
        r = len(pizza)
        c = len(pizza[0])
        
        # 2D prefix sum of apples
        pref = [[0] * (c + 1) for _ in range(r + 1)]
        for i in range(r):
            for j in range(c):
                pref[i+1][j+1] = (pref[i][j+1] + pref[i+1][j] - pref[i][j] +
                                  (1 if pizza[i][j] == 'A' else 0))
        
        total_apples = pref[r][c]
        if total_apples < k:
            return 0
        
        @lru_cache(None)
        def dp(i: int, j: int, cuts: int) -> int:
            # returns number of ways to cut rectangle (i,j) to (r-1,c-1) into 'cuts' pieces
            # each piece must contain at least one apple
            if cuts == 1:
                # check if this rectangle has at least one apple
                apples = (pref[r][c] - pref[i][c] - pref[r][j] + pref[i][j])
                return 1 if apples > 0 else 0
            
            total = 0
            # horizontal cuts: try to cut between rows
            for row in range(i, r - 1):
                # top piece: rows i..row, columns j..c-1
                top_apples = (pref[row+1][c] - pref[i][c] - pref[row+1][j] + pref[i][j])
                if top_apples > 0:
                    total += dp(row + 1, j, cuts - 1)
                    total %= MOD
            # vertical cuts: try to cut between columns
            for col in range(j, c - 1):
                # left piece: rows i..r-1, columns j..col
                left_apples = (pref[r][col+1] - pref[i][col+1] - pref[r][j] + pref[i][j])
                if left_apples > 0:
                    total += dp(i, col + 1, cuts - 1)
                    total %= MOD
            return total % MOD
        
        return dp(0, 0, k) % MOD