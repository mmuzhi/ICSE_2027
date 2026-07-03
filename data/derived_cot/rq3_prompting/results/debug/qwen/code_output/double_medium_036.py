class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        doubled = toppingCosts * 2
        
        @cache
        def fn(i, x):
            if x < 0 or i == len(doubled):
                return 0
            take = doubled[i] + fn(i+1, x - doubled[i])
            skip = fn(i+1, x)
            return min(take, skip, key=lambda y: (abs(y - x), y))
        
        ans = float('inf')
        for bc in baseCosts:
            best_topping = fn(0, target - bc)
            total = bc + best_topping
            if abs(total - target) < abs(ans - target) or (abs(total - target) == abs(ans - target) and total < ans):
                ans = total
        return ans