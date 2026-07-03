class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        if k == 0:
            return 1 if self.hasApple(0, 0, self.r-1, self.c-1) else 0
        
        # Build 2D prefix sum array
        pref = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(1, self.r + 1):
            for j in range(1, self.c + 1):
                val = 1 if pizza[i-1][j-1] == 'A' else 0
                pref[i][j] = val + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1]
        
        from functools import lru_cache
        @lru_cache(maxsize=None)
        def dfs(i, j, k):
            if k == 0:
                return 1 if self.hasApple(i, j, self.r-1, self.c-1, pref) else 0
            
            total = 0
            
            # Horizontal cuts
            for x in range(i+1, self.r):
                if self.hasApple(i, j, x, self.c-1, pref) and self.hasApple(x+1, j, self.r-1, self.c-1, pref):
                    total += dfs(x+1, j, k-1)
            
            # Vertical cuts
            for y in range(j+1, self.c):
                if self.hasApple(i, j, self.r-1, y-1, pref) and self.hasApple(i, y, self.r-1, self.c-1, pref):
                    total += dfs(i, y, k-1)
            
            return total % 1000000007
        
        return dfs(0, 0, k) % 1000000007

    def hasApple(self, i, j, x, y, pref=None):
        if pref is None:
            # Fallback if no prefix sum is provided (for small cases)
            if i > x or j > y:
                return False
            for r in range(i, x+1):
                for c in range(j, y+1):
                    if self.pizza[r][c] == 'A':
                        return True
            return False
        else:
            return (pref[x+1][y+1] - pref[i][y+1] - pref[x+1][j] + pref[i][j]) > 0