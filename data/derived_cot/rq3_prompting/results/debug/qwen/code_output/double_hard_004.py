from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        mod = 1000000007
        r = len(pizza)
        c = len(pizza[0])
        
        # Build 2D prefix sum for the entire pizza
        pref = [[0] * (c+1) for _ in range(r+1)]
        for i in range(r):
            for j in range(c):
                if pizza[i][j] == 'A':
                    pref[i+1][j+1] = 1
                pref[i+1][j+1] += pref[i][j+1] + pref[i+1][j] - pref[i][j]
        
        total_apples = pref[r][c]
        if total_apples < k:
            return 0
        
        if k > r * c:
            return 0
        
        def has_apple(i1, j1, i2, j2):
            if i1 > i2 or j1 > j2:
                return False
            total = pref[i2+1][j2+1] - pref[i1][j2+1] - pref[i2+1][j1] + pref[i1][j1]
            return total > 0
        
        @cache
        def getWays(i, j, k):
            if k == 1:
                return 1 if has_apple(i, j, r-1, c-1) else 0
            
            ways = 0
            for cut in range(i+1, r):
                if has_apple(i, j, cut-1, c-1) and has_apple(cut, j, r-1, c-1):
                    ways = (ways + getWays(cut, j, k-1)) % mod
            
            for cut in range(j+1, c):
                if has_apple(i, j, r-1, cut-1) and has_apple(i, cut, r-1, c-1):
                    ways = (ways + getWays(i, cut, k-1)) % mod
            
            return ways % mod
        
        return getWays(0, 0, k) % mod