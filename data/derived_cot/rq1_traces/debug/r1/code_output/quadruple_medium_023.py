from typing import List
from functools import cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        @cache
        def fn(i, x):
            """Return sum of toppings from toppingCosts[i:] closest to x."""
            if x < 0 or i >= len(toppingCosts):
                return 0
            cost = toppingCosts[i]
            option0 = fn(i + 1, x)
            option1 = cost + fn(i + 1, x - cost)
            option2 = 2 * cost + fn(i + 1, x - 2 * cost)
            return min(option0, option1, option2, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            current = bc + fn(0, target - bc)
            ans = min(ans, current, key=lambda x: (abs(x - target), x))
        return ans