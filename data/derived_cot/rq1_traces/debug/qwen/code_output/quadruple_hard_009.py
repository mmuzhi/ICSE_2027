class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        mod = 1000000007
        m = len(pizza)
        n = len(pizza[0])
        grid = [[0]*n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if pizza[i][j] == 'A':
                    grid[i][j] = 1
        
        pref = [[0]*(n+1) for _ in range(m+1)]
        for i in range(1, m+1):
            for j in range(1, n+1):
                pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + grid[i-1][j-1]
        
        def has_apple(r1, c1, r2, c2):
            return (pref[r2][c2] - pref[r1][c2] - pref[r2][c1] + pref[r1][c1]) > 0
        
        from functools import lru_cache
        @lru_cache(maxsize=None)
        def dp(i, j, k):
            if k == 1:
                return 1 if has_apple(i, j, m, n) else 0
            total = 0
            for r in range(i+1, m):
                if has_apple(i, j, r, n) and has_apple(r, j, m, n):
                    for a in range(1, k):
                        b = k - a
                        total = (total + dp(i, j, a) * dp(r, j, b)) % mod
            for c in range(j+1, n):
                if has_apple(i, j, m, c) and has_apple(i, c, m, n):
                    for b in range(1, k):
                        a = k - b
                        total = (total + dp(i, j, a) * dp(i, c, b)) % mod
            return total % mod
        
        return dp(0, 0, k) % mod