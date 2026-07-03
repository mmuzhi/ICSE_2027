from typing import List
from functools import cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts = toppingCosts * 2  # Create a new list with each topping duplicated

        @cache
        def fn(i: int, x: int) -> int:
            if x < 0 or i == len(toppingCosts):
                return 0
            not_take = fn(i + 1, x)
            take = toppingCosts[i] + fn(i + 2, x - toppingCosts[i])
            return min(not_take, take, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            current_total = bc + fn(0, target - bc)
            ans = min(ans, current_total, key=lambda z: (abs(z - target), z))
        return ans