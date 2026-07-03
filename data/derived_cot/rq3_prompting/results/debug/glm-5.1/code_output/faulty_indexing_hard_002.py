from typing import List

class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        items.sort(key=lambda x: -x[0])
        total_profit = 0
        seen = set()
        duplicates = []
        ans = 0
        
        for i in range(len(items)):
            profit, category = items[i]
            if i < k:
                total_profit += profit
                if category in seen:
                    duplicates.append(profit)
                else:
                    seen.add(category)
            else:
                if category not in seen and duplicates:
                    seen.add(category)
                    total_profit += profit - duplicates.pop()
            
            if i >= k - 1:
                ans = max(ans, total_profit + len(seen)**2)
                
        return ans