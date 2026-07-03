from collections import defaultdict

class Solution:
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:
        dico = defaultdict(list)
        for profit, category in items:
            dico[category].append(profit)
        categories = []
        for category in dico:
            categories.append(sorted(dico[category]))
        categories.sort(key=lambda x: x[-1], reverse=True)
        
        def elegance(distinct):
            res = 0
            rest = []
            for i in range(distinct):
                res += categories[i][-1]
                for j in range(len(categories[i])-1):
                    rest.append(categories[i][j])
            rest.sort(reverse=True)
            if len(rest) < k - distinct:
                return -1
            return res + sum(rest[:k-distinct]) + distinct**2
        
        best = -1
        max_distinct = min(len(categories), k)
        for distinct in range(1, max_distinct+1):
            val = elegance(distinct)
            if val == -1:
                continue
            if val > best:
                best = val
        return best