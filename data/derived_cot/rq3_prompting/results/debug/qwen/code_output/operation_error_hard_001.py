class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        r = len(pizza)
        c = len(pizza[0])
        
        # Build a 2D prefix sum array for the entire pizza
        pref = [[0]*(c+1) for _ in range(r+1)]
        for i in range(r):
            for j in range(c):
                pref[i+1][j+1] = pref[i][j+1] + pref[i+1][j] - pref[i][j] + (1 if pizza[i][j]=='A' else 0)
        
        # Helper function to get the number of apples in a rectangle
        def get_apples(i1, j1, i2, j2):
            if i1 > i2 or j1 > j2:
                return 0
            return pref[i2+1][j2+1] - pref[i1][j2+1] - pref[i2+1][j1] + pref[i1][j1]
        
        # DFS with memoization
        from functools import lru_cache
        @lru_cache(maxsize=None)
        def dfs(i, j, cuts):
            if cuts == 0:
                if get_apples(i, j, r-1, c-1) > 0:
                    return 1
                else:
                    return 0
            
            total = 0
            
            # Horizontal cuts
            for r_cut in range(i+1, r):
                if get_apples(i, j, r_cut-1, c-1) == 0:
                    continue
                if get_apples(r_cut, j, r-1, c-1) == 0:
                    continue
                for x in range(0, cuts):
                    y = cuts - 1 - x
                    if y < 0:
                        break
                    total += dfs(i, j, x) * dfs(r_cut, j, y)
            
            # Vertical cuts
            for col_cut in range(j+1, c):
                if get_apples(i, j, r-1, col_cut-1) == 0:
                    continue
                if get_apples(i, col_cut, r-1, c-1) == 0:
                    continue
                for y in range(0, cuts):
                    x = cuts - 1 - y
                    if x < 0:
                        break
                    total += dfs(i, j, x) * dfs(i, col_cut, y)
            
            return total
        
        return dfs(0, 0, k) % 1000000007