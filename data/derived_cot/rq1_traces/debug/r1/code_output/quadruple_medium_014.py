from typing import List
from functools import cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts = toppingCosts * 2  # Allow each topping to be used up to two times

        @cache
        def fn(i, x):
            """Return the sum of subsequence of toppingCosts[i:] closest to x."""
            if x < 0 or i == len(toppingCosts):
                return 0
            # Consider two options: skip current topping or take it
            skip = fn(i + 1, x)
            take = toppingCosts[i] + fn(i + 1, x - toppingCosts[i])
            # Choose the closest to x, preferring smaller sum on tie
            return min(skip, take, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            current = bc + fn(0, target - bc)
            ans = min(ans, current, key=lambda x: (abs(x - target), x))
        return ans