from functools import lru_cache
from typing import List

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = sorted(cuts + [0, n])
        
        @lru_cache(None)
        def dfs(l, r):
            length = cuts[r] - cuts[l]
            if l + 1 >= r:
                return 0
            return min(dfs(l, i) + dfs(i, r) for i in range(l + 1, r)) + length
        
        return dfs(0, len(cuts) - 1)