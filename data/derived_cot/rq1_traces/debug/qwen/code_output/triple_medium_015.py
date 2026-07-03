class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2
        
        from functools import cache
        
        @cache
        def fn(i, x):
            if x < 0 or i == len(toppingCosts):
                return 0
            not_take = fn(i+1, x)
            take = toppingCosts[i] + fn(i+1, x - toppingCosts[i])
            not_take_diff = abs(not_take - x)
            take_diff = abs(take - x)
            if not_take_diff < take_diff:
                return not_take
            elif take_diff < not_take_diff:
                return take
            else:
                return min(not_take, take)
        
        ans = float('inf')
        for bc in baseCosts:
            res = fn(0, target - bc)
            total = bc + res
            diff = abs(total - target)
            if diff < abs(ans - target):
                ans = total
            elif diff == abs(ans - target) and total < ans:
                ans = total
        return ans