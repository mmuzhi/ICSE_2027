class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2
        from functools import cache
        
        @cache
        def fn(i, x):
            if x < 0 or i == len(toppingCosts):
                return 0
            candidate1 = fn(i+2, x)
            candidate2 = toppingCosts[i] + fn(i+1, x - toppingCosts[i])
            return min(candidate1, candidate2, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            total = bc + fn(0, target - bc)
            if abs(total - target) < abs(ans - target):
                ans = total
            elif abs(total - target) == abs(ans - target) and total < ans:
                ans = total
        return ans