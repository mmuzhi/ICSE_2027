class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2

        from functools import cache
        @cache
        def fn(i, x):
            """Return sum of subsequence of toppingCosts[i:] closest to x."""
            if x < 0 or i == len(toppingCosts):
                return 0
            not_taken = fn(i+1, x)
            taken = toppingCosts[i] + fn(i+2, x - toppingCosts[i])
            return min(not_taken, taken, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts: 
            ans = min(ans, bc + fn(0, target - bc), key=lambda x: (abs(x - target), x))
        return ans