from typing import List
from functools import lru_cache

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = [0] + sorted(cuts) + [n]
        m = len(cuts)
        
        @lru_cache(maxsize=None)
        def dfs(l, r):
            if r == l + 1:
                return 0
            min_cost = float('inf')
            for k in range(l + 1, r):
                cost_here = dfs(l, k) + dfs(k, r) + (cuts[r] - cuts[l])
                if cost_here < min_cost:
                    min_cost = cost_here
            return min_cost
        
        return dfs(0, m - 1)