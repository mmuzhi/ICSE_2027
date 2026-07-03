MOD = 1000000007

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        r = len(pizza)
        c = len(pizza[0])
        
        # Build the prefix sum array
        prefix = [[0] * (c+1) for _ in range(r+1)]
        for i in range(1, r+1):
            for j in range(1, c+1):
                val = 1 if pizza[i-1][j-1] == 'A' else 0
                prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + val
        
        total_apples = prefix[r][c]
        if total_apples < k:
            return 0
        
        def get_rect_apples(top, bottom, left, right):
            return prefix[bottom+1][right+1] - prefix[top][right+1] - prefix[bottom+1][left] + prefix[top][left]
        
        from functools import cache
        @cache
        def getWays(top, bottom, left, right, k):
            if k == 1:
                return 1 if get_rect_apples(top, bottom, left, right) > 0 else 0
            total = 0
            for i in range(top+1, bottom+1):
                if get_rect_apples(top, i-1, left, right) > 0 and get_rect_apples(i, bottom, left, right) > 0:
                    total = (total + getWays(top, i-1, left, right, k-1) + getWays(i, bottom, left, right, k-1)) % MOD
            for j in range(left+1, right+1):
                if get_rect_apples(top, bottom, left, j-1) > 0 and get_rect_apples(top, bottom, j, right) > 0:
                    total = (total + getWays(top, bottom, left, j-1, k-1) + getWays(top, bottom, j, right, k-1)) % MOD
            return total
        
        return getWays(0, r-1, 0, c-1, k) % MOD