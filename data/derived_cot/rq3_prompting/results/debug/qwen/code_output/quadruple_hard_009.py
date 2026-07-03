class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        mod = 1000000007
        self.r = len(pizza)
        self.c = len(pizza[0])
        s = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r):
            for j in range(self.c):
                if pizza[i][j] == 'A':
                    s[i+1][j+1] = s[i][j+1] + s[i+1][j] - s[i][j] + 1
                else:
                    s[i+1][j+1] = s[i][j+1] + s[i+1][j] - s[i][j]
        
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dp(i, j, k):
            if s[self.r][self.c] - s[i][self.c] - s[self.r][j] + s[i][j] == 0:
                return 0
            if k == 0:
                return 1
            ways = 0
            for x in range(i+1, self.r):
                top = s[x+1][self.c] - s[i][self.c] - s[x+1][j] + s[i][j]
                bottom = s[self.r][self.c] - s[x+1][self.c] - s[self.r][j] + s[x+1][j]
                if top > 0 and bottom > 0:
                    ways = (ways + dp(i, j, k-1) * dp(x+1, j, k-1)) % mod
            for y in range(j+1, self.c):
                left = s[self.r][y] - s[i][y] - s[self.r][j] + s[i][j]
                right = s[self.r][self.c] - s[self.r][y+1] - s[self.r][j] + s[i][j]
                if left > 0 and right > 0:
                    ways = (ways + dp(i, j, k-1) * dp(i, y+1, k-1)) % mod
            return ways
        
        return dp(0, 0, k) % mod