class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts = toppingCosts * 2
        
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def fn(i, x):
            if x < 0 or i >= len(toppingCosts):
                return 0
            skip = fn(i+2, x)
            use = toppingCosts[i] + fn(i+1, x - toppingCosts[i])
            return min(skip, use, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            topping_sum = fn(0, target - bc)
            total = bc + topping_sum
            if abs(total - target) < abs(ans - target):
                ans = total
            elif abs(total - target) == abs(ans - target) and total < ans:
                ans = total
        return ans