MOD = 1000000007

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        
        # Build a 1-indexed prefix sum array
        pref = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r):
            for j in range(self.c):
                val = 1 if pizza[i][j] == 'A' else 0
                pref[i+1][j+1] = val + pref[i][j+1] + pref[i+1][j] - pref[i][j]
        
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def has_apple(i1, j1, i2, j2):
            if i1 > i2 or j1 > j2:
                return False
            total = pref[i2+1][j2+1] - pref[i1][j2+1] - pref[i2+1][j1] + pref[i1][j1]
            return total > 0
        
        @lru_cache(maxsize=None)
        def dfs(i, j, k):
            if k == 1:
                return 1 if has_apple(i, j, self.r-1, self.c-1) else 0
            
            total_ways = 0
            
            # Horizontal cuts
            for x in range(i+1, self.r):
                if has_apple(i, j, x-1, self.c-1) and has_apple(x, j, self.r-1, self.c-1):
                    total_ways = (total_ways + dfs(x, j, k-1)) % MOD
            
            # Vertical cuts
            for y in range(j+1, self.c):
                if has_apple(i, j, self.r-1, y-1) and has_apple(i, y, self.r-1, self.c-1):
                    total_ways = (total_ways + dfs(i, y, k-1)) % MOD
            
            return total_ways
        
        return dfs(0, 0, k) % MOD