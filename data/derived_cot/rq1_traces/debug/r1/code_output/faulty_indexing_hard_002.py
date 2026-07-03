from typing import List

class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        items.sort(key=lambda x: x[0], reverse=True)
        total = 0
        seen = set()
        dup = []
        for i in range(k):
            profit, category = items[i]
            total += profit
            if category in seen:
                dup.append(profit)
            else:
                seen.add(category)
        dup.sort()
        best_unseen = []
        included = set()
        for i in range(len(items)):
            profit, category = items[i]
            if category not in seen:
                if category not in included:
                    included.add(category)
                    best_unseen.append(profit)
        best_unseen.sort(reverse=True)
        res = total + len(seen) ** 2
        for i in range(min(len(dup), len(best_unseen))):
            total = total - dup[i] + best_unseen[i]
            distinct = len(seen) + i + 1
            res = max(res, total + distinct * distinct)
        return res