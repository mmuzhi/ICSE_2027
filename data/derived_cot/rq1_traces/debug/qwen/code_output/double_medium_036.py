class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        from functools import cache
        
        @cache
        def fn(x):
            if x <= 0:
                return 0
            best_val = 0
            best_diff = float('inf')
            for t in toppingCosts:
                candidate = t + fn(x - t)
                diff = abs(candidate - x)
                if diff < best_diff:
                    best_diff = diff
                    best_val = candidate
                elif diff == best_diff and candidate < best_val:
                    best_val = candidate
            return best_val
        
        ans = float('inf')
        for bc in baseCosts:
            remaining = target - bc
            topping_cost = fn(remaining)
            total = bc + topping_cost
            diff_total = abs(total - target)
            if diff_total < abs(ans - target):
                ans = total
            elif diff_total == abs(ans - target) and total < ans:
                ans = total
        return ans