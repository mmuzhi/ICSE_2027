from typing import List
from functools import lru_cache

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = sorted(cuts + [0, n])
        
        @lru_cache(maxsize=None)
        def dfs(l, r):
            if r - l == 1:
                return 0
            length = cuts[r] - cuts[l]
            min_cost = float('inf')
            for i in range(l+1, r):
                cost = dfs(l, i) + dfs(i, r)
                if cost < min_cost:
                    min_cost = cost
            return min_cost + length
        
        return dfs(0, len(cuts)-1)