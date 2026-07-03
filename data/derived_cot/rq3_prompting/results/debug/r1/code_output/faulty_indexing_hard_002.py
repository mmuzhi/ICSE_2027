from typing import List
from collections import defaultdict
import heapq

class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        # group profits by category
        dico = defaultdict(list)
        for profit, category in items:
            dico[category].append(profit)
        
        # sort each category's profits descending
        groups = []
        for profits in dico.values():
            profits.sort(reverse=True)
            groups.append(profits)
        
        # sort categories by their maximum profit descending
        groups.sort(key=lambda x: x[0], reverse=True)
        
        best = 0
        total_max = 0          # sum of the selected maximum profits
        heap = []              # min-heap of the largest (k-d) non-max profits
        rest_sum = 0           # sum of elements in heap
        
        for i, group in enumerate(groups):
            d = i + 1          # number of distinct categories used
            if d > k:          # cannot have more distinct categories than k
                break
            
            # adjust heap to the new limit (k-d) by removing the smallest items
            while len(heap) > k - d:
                removed = heapq.heappop(heap)
                rest_sum -= removed
            
            # take the maximum profit from this category
            total_max += group[0]
            
            # add all other profits of this category into the pool
            for profit in group[1:]:
                heapq.heappush(heap, profit)
                rest_sum += profit
                # keep only the largest (k-d) items
                if len(heap) > k - d:
                    removed = heapq.heappop(heap)
                    rest_sum -= removed
            
            # if we have exactly (k-d) additional items, it's a valid selection
            if len(heap) == k - d:
                candidate = total_max + rest_sum + d * d
                if candidate > best:
                    best = candidate
        
        return best