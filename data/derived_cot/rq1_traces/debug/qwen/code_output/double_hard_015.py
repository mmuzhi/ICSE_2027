from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        # Build a grid of apples (1 for 'A', 0 otherwise)
        grid = [[0]*self.c for _ in range(self.r)]
        for i in range(self.r):
            for j in range(self.c):
                if pizza[i][j] == 'A':
                    grid[i][j] = 1
        
        # Build a 2D prefix sum array `pref` of size (self.r+1) x (self.c+1)
        pref = [[0]*(self.c+1) for _ in range(self.r+1)]
        for i in range(1, self.r+1):
            for j in range(1, self.c+1):
                pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + grid[i-1][j-1]
        
        # Define a helper function to get the number of apples in a rectangle [r1, r2] x [c1, c2]
        def get_apples(r1, c1, r2, c2):
            if r1 > r2 or c1 > c2:
                return 0
            return pref[r2+1][c2+1] - pref[r1][c2+1] - pref[r2+1][c1] + pref[r1][c1]
        
        # Define a recursive function with memoization
        @cache
        def getWays(i, j, k_val):
            if k_val < 0:
                return 0
            if get_apples(i, j, self.r-1, self.c-1) == 0:
                return 0
            if k_val == 0:
                return 1
            total = 0
            # Horizontal cuts
            for r in range(i+1, self.r):
                if get_apples(i, j, r-1, self.c-1) > 0 and get_apples(r, j, self.r-1, self.c-1) > 0:
                    for a in range(0, k_val):
                        total = (total + getWays(i, j, a) * getWays(r, j, k_val-1-a)) % (1000000007)
            # Vertical cuts
            for c in range(j+1, self.c):
                if get_apples(i, j, self.r-1, c-1) > 0 and get_apples(i, c, self.r-1, self.c-1) > 0:
                    for a in range(0, k_val):
                        total = (total + getWays(i, j, a) * getWays(i, c, k_val-1-a)) % (1000000007)
            return total
        
        total_ways = 0
        for cuts in range(0, k+1):
            total_ways = (total_ways + getWays(0, 0, cuts)) % (1000000007)
        return total_ways