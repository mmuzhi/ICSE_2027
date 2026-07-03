class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2
        
        from functools import cache
        
        @cache
        def fn(i, x):
            if x < 0 or i >= len(toppingCosts):
                return 0
            return min(
                fn(i+2, x),
                toppingCosts[i] + fn(i+1, x - toppingCosts[i]),
                key=lambda y: (abs(y - x), y)
            )
        
        ans = float('inf')
        for bc in baseCosts:
            res = fn(0, target - bc)
            if abs(ans) > abs(res):
                ans = res
            elif abs(ans) == abs(res) and ans > res:
                ans = res
        return ans + min(baseCosts) if ans < 0 else ans + min(baseCosts) if ans < 0 else ans