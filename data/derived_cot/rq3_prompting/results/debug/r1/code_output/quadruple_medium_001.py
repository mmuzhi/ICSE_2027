from typing import List
from functools import cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        # duplicate toppings so each appears twice consecutively
        toppingCosts = [t for t in toppingCosts for _ in range(2)]

        @cache
        def fn(i: int, x: int) -> int:
            """Return sum of subsequence of toppingCosts[i:] closest to x."""
            if x < 0 or i >= len(toppingCosts):
                return 0
            # skip current topping (both copies)
            skip = fn(i + 2, x)
            # take one copy of current topping
            take = toppingCosts[i] + fn(i + 1, x - toppingCosts[i])
            return min(skip, take, key=lambda y: (abs(y - x), y))

        ans = float('inf')
        for bc in baseCosts:
            ans = min(ans, bc + fn(0, target - bc), key=lambda x: (abs(x - target), x))
        return ans