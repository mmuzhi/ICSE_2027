from functools import lru_cache

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts = toppingCosts * 2
        
        @lru_cache(maxsize=None)
        def fn(i, x):
            if x < 0 or i == len(toppingCosts):
                return 0
            not_take = fn(i+1, x)
            take = toppingCosts[i] + fn(i+1, x - toppingCosts[i])
            if abs(not_take - x) <= abs(take - x):
                return not_take
            else:
                return take
        
        ans = float('inf')
        for bc in baseCosts:
            total = bc + fn(0, target - bc)
            if abs(total - target) < abs(ans - target) or (abs(total - target) == abs(ans - target) and total < ans):
                ans = total
        return ans