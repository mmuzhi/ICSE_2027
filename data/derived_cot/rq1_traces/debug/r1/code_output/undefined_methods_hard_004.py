from functools import lru_cache
from typing import List

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = sorted(cuts + [0, n])
        
        @lru_cache(maxsize=None)
        def dfs(l, r):
            length = cuts[r] - cuts[l]
            M = range(l+1, r)
            return min((dfs(l, i) + dfs(i, r) for i in M), default=-length) + length
        
        return dfs(0, len(cuts)-1)