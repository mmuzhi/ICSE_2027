class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        toppingCosts *= 2
        
        from functools import cache
        
        @cache
        def fn(i, x):
            if x < 0 or i == len(toppingCosts):
                return 0
            
            skip = fn(i+1, x)
            take_one = float('inf')
            if x >= toppingCosts[i]:
                take_one = toppingCosts[i] + fn(i+1, x - toppingCosts[i])
            
            take_two = float('inf')
            if i+1 < len(toppingCosts) and toppingCosts[i] == toppingCosts[i+1] and x >= toppingCosts[i] + toppingCosts[i+1]:
                take_two = toppingCosts[i] + toppingCosts[i+1] + fn(i+2, x - toppingCosts[i] - toppingCosts[i+1])
            
            candidates = [skip, take_one, take_two]
            candidates = [c for c in candidates if c != float('inf')]
            
            if not candidates:
                return 0
            
            best = min(candidates, key=lambda y: (abs(y - x), y))
            return best
        
        ans = float('inf')
        for bc in baseCosts:
            total = bc + fn(0, target - bc)
            if abs(total - target) < abs(ans - target) or (abs(total - target) == abs(ans - target) and total < ans):
                ans = total
                
        return ans