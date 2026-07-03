from typing import List
from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 1000000007
        rows = len(pizza)
        cols = len(pizza[0])
        
        # 2D prefix sum: ps[i][j] = total apples in rectangle (0,0) to (i-1, j-1)
        ps = [[0] * (cols + 1) for _ in range(rows + 1)]
        for i in range(rows):
            for j in range(cols):
                ps[i+1][j+1] = (ps[i+1][j] + ps[i][j+1] - ps[i][j] +
                                (1 if pizza[i][j] == 'A' else 0))
        
        def has_apple(r1, c1, r2, c2) -> bool:
            # rectangle inclusive: (r1,c1) to (r2,c2)
            if r1 > r2 or c1 > c2:
                return False
            total = (ps[r2+1][c2+1] - ps[r1][c2+1] -
                     ps[r2+1][c1] + ps[r1][c1])
            return total > 0
        
        @cache
        def dfs(top, left, cuts) -> int:
            # cuts = number of cuts still to make (total cuts = k-1)
            if cuts == 0:
                # last piece must contain at least one apple
                return 1 if has_apple(top, left, rows-1, cols-1) else 0
            
            ways = 0
            # horizontal cuts: cut after row i (top <= i < rows-1)
            for i in range(top, rows - 1):
                if has_apple(top, left, i, cols-1):
                    ways += dfs(i + 1, left, cuts - 1)
            # vertical cuts: cut after column j (left <= j < cols-1)
            for j in range(left, cols - 1):
                if has_apple(top, left, rows-1, j):
                    ways += dfs(top, j + 1, cuts - 1)
            return ways % MOD
        
        # total apples check
        total_apples = sum(row.count('A') for row in pizza)
        if total_apples < k:
            return 0
        
        return dfs(0, 0, k - 1) % MOD