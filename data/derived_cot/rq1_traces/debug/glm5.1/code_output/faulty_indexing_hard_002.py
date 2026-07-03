class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        items.sort(key=lambda x: -x[0])
        seen = set()
        cur_sum = 0
        duplicates = []
        
        for i in range(k):
            profit, category = items[i]
            cur_sum += profit
            if category in seen:
                duplicates.append(profit)
            else:
                seen.add(category)
        
        res = cur_sum + len(seen) ** 2
        
        for i in range(k, len(items)):
            profit, category = items[i]
            if category not in seen and duplicates:
                seen.add(category)
                cur_sum += profit - duplicates.pop()
                res = max(res, cur_sum + len(seen) ** 2)
                
        return res