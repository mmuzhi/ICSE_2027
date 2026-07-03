class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        from functools import cache

        @cache
        def fn(i, x):
            """Return sum of toppingCosts[i:] closest to x."""
            if x < 0 or i == len(toppingCosts):
                return 0
            ans = fn(i+1, x)
            ans = min(ans, toppingCosts[i] + fn(i+1, x-toppingCosts[i]), key=lambda y: (abs(y-x), y))
            ans = min(ans, toppingCosts[i]*2 + fn(i+1, x-toppingCosts[i]*2), key=lambda y: (abs(y-x), y))
            return ans

        ans = float('inf')
        for bc in baseCosts:
            ans = min(ans, bc + fn(0, target - bc), key=lambda x: (abs(x-target), x))
        return ans