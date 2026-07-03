from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        r_total = len(pizza)
        if r_total == 0:
            return 0
        c_total = len(pizza[0])
        
        apples = [[0] * c_total for _ in range(r_total)]
        for i in range(r_total):
            for j in range(c_total):
                if pizza[i][j] == 'A':
                    apples[i][j] = 1
        
        pref = [[0] * (c_total + 1) for _ in range(r_total + 1)]
        for i in range(1, r_total + 1):
            for j in range(1, c_total + 1):
                pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + apples[i-1][j-1]
        
        def get_rect(i1, i2, j1, j2):
            if i1 > i2 or j1 > j2:
                return 0
            return pref[i2+1][j2+1] - pref[i1][j2+1] - pref[i2+1][j1] + pref[i1][j1]
        
        if get_rect(0, r_total-1, 0, c_total-1) < k:
            return 0
        
        @lru_cache(maxsize=None)
        def f(i, j, k):
            total = get_rect(i, r_total-1, j, c_total-1)
            if total < k:
                return 0
            if k == 1:
                return 1
            
            res = 0
            for r in range(i+1, r_total):
                top_apples = get_rect(i, r-1, j, c_total-1)
                if top_apples == 0:
                    continue
                bottom_apples = get_rect(r, r_total-1, j, c_total-1)
                if bottom_apples == 0:
                    continue
                for a in range(1, k):
                    res = (res + f(i, j, a) * f(r, j, k - a)) % 1000000007
            
            for c in range(j+1, c_total):
                left_apples = get_rect(i, r_total-1, j, c-1)
                if left_apples == 0:
                    continue
                right_apples = get_rect(i, r_total-1, c, c_total-1)
                if right_apples == 0:
                    continue
                for a in range(1, k):
                    res = (res + f(i, j, a) * f(i, c, k - a)) % 1000000007
            
            return res
        
        return f(0, 0, k) % 1000000007