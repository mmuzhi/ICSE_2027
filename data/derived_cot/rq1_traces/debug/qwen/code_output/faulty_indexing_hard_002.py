from collections import defaultdict

class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        dico = defaultdict(list)
        for profit, category in items:
            dico[category].append(profit)
        max_profits = [max(profits) for profits in dico.values()]
        max_profits.sort(reverse=True)
        if len(max_profits) < k:
            return -1
        return sum(max_profits[:k])