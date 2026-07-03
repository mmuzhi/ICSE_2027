from typing import List
from functools import cache
import math

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2  # duplicate to allow up to 2 of each topping

        @cache
        def fn(i: int, x: int) -> int:
            """Return the sum of a subsequence of toppingCosts[i:] closest to x."""
            if x < 0 or i == len(toppingCosts):
                return 0
            # Option 1: skip current topping
            skip = fn(i + 1, x)
            # Option 2: take current topping
            take = toppingCosts[i] + fn(i + 1, x - toppingCosts[i])
            # Choose the one with smaller absolute difference, tie goes to smaller sum
            return min(skip, take, key=lambda y: (abs(y - x), y))

        ans = math.inf
        for bc in baseCosts:
            ans = min(ans, bc + fn(0, target - bc), key=lambda x: (abs(x - target), x))
        return ans