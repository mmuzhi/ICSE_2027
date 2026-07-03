class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        from functools import cache
        
        @cache
        def fn(i, x):
            if i >= len(toppingCosts) or x < 0:
                return 0
            candidate1 = fn(i+1, x)
            candidate2 = toppingCosts[i] + fn(i, x - toppingCosts[i])
            return min(candidate1, candidate2, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            total = bc + fn(0, target - bc)
            ans = min(ans, total, key=lambda x: (abs(x - target), x))
        return ans