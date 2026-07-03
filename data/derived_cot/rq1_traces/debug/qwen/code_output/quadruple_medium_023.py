class Solution:
    def closestCost(self, baseCosts: list[int], toppingCosts: list[int], target: int) -> int:
        toppingCosts_doubled = toppingCosts * 2
        n = len(toppingCosts_doubled)
        from functools import cache
        
        @cache
        def fn(i, x):
            if i >= n or x <= 0:
                return 0
            candidates = [fn(i+2, x)]
            candidates.append(toppingCosts_doubled[i] + fn(i+1, x - toppingCosts_doubled[i]))
            return min(candidates, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            extra = fn(0, target - bc)
            total = bc + extra
            ans = min(ans, total, key=lambda x: (abs(x - target), x))
        return ans