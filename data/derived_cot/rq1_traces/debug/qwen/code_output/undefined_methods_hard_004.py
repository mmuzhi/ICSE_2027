from typing import List
from functools import lru_cache

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts_list = sorted([0, n] + cuts)
        m = len(cuts_list)
        
        @lru_cache(maxsize=None)
        def dfs(l, r):
            if r == l + 1:
                return 0
            length = cuts_list[r] - cuts_list[l]
            min_cost = float('inf')
            for k in range(l + 1, r):
                cost = dfs(l, k) + dfs(k, r)
                if cost < min_cost:
                    min_cost = cost
            return min_cost + length
        
        return dfs(0, m - 1)