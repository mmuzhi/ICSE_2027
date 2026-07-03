from typing import List
from functools import lru_cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2
        n = len(toppingCosts)
        
        @lru_cache(None)
        def fn(i: int, x: int) -> int:
            if x < 0:
                return 0
            if i == n:
                return 0
            skip = fn(i + 1, x)
            take = toppingCosts[i] + fn(i + 1, x - toppingCosts[i])
            return min(skip, take, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            total = bc + fn(0, target - bc)
            ans = min(ans, total, key=lambda x: (abs(x - target), x))
        return ans