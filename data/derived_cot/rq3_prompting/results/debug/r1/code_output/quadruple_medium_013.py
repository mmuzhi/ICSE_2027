from typing import List
from functools import lru_cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        # Double the topping list so each topping can be used up to twice.
        toppingCosts *= 2

        @lru_cache(None)
        def fn(i: int, x: int) -> int:
            """Return sum of subsequence of toppingCosts[i:] closest to x."""
            if i == len(toppingCosts) or x < 0:
                return 0
            # Option 1: skip the current topping
            skip = fn(i + 1, x)
            # Option 2: take the current topping (use it once)
            take = toppingCosts[i] + fn(i + 1, x - toppingCosts[i])
            # Return the sum that is closest to x (ties broken by smaller sum)
            return min(skip, take, key=lambda y: (abs(y - x), y))

        ans = float('inf')
        for bc in baseCosts:
            cur = bc + fn(0, target - bc)
            ans = min(ans, cur, key=lambda x: (abs(x - target), x))
        return ans