class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2
        
        from functools import cache
        
        @cache
        def fn(i, x):
            if i == len(toppingCosts) or x <= 0:
                return 0
            return min(fn(i+1, x), toppingCosts[i] + fn(i+1, x - toppingCosts[i]), key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            candidate = bc + fn(0, target - bc)
            ans = min(ans, candidate, key=lambda x: (abs(x - target), x))
        return ans