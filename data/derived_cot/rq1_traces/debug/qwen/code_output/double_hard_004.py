class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        mod = 1000000007
        n = len(pizza)
        m = len(pizza[0])
        pref = [[0]*(m+1) for _ in range(n+1)]
        for i in range(n):
            for j in range(m):
                val = 1 if pizza[i][j] == 'A' else 0
                pref[i+1][j+1] = val + pref[i][j+1] + pref[i+1][j] - pref[i][j]
        
        def get_apples(r1, c1, r2, c2):
            return pref[r2+1][c2+1] - pref[r1][c2+1] - pref[r2+1][c1] + pref[r1][c1]
        
        if get_apples(0, 0, n-1, m-1) < k:
            return 0
        
        from functools import lru_cache
        @lru_cache(maxsize=None)
        def dp(i, j, k):
            if k == 1:
                if get_apples(i, j, n-1, m-1) > 0:
                    return 1
                return 0
            
            ways = 0
            
            for x in range(i, n-1):
                top = get_apples(i, j, x, m-1)
                bottom = get_apples(x+1, j, n-1, m-1)
                if top > 0 and bottom >= k-1:
                    ways = (ways + dp(x+1, j, k-1)) % mod
            
            for y in range(j, m-1):
                left = get_apples(i, j, n-1, y)
                right = get_apples(i, y+1, n-1, m-1)
                if left > 0 and right >= k-1:
                    ways = (ways + dp(i, y+1, k-1)) % mod
            
            return ways
        
        return dp(0, 0, k) % mod