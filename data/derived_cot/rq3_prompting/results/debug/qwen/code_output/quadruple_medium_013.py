class Solution:
    def closestCost(self, baseCosts: list[int], toppingCosts: list[int], target: int) -> int:
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def fn(i, x):
            if x <= 0:
                return 0
            if i >= len(toppingCosts):
                return 0
            use0 = fn(i+1, x)
            use1 = toppingCosts[i] + fn(i+1, x - toppingCosts[i])
            use2 = toppingCosts[i] * 2 + fn(i+1, x - toppingCosts[i] * 2)
            return min(use0, use1, use2, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            remaining = target - bc
            topping_part = fn(0, remaining)
            total_cost = bc + topping_part
            if abs(total_cost - target) < abs(ans - target):
                ans = total_cost
        return ans