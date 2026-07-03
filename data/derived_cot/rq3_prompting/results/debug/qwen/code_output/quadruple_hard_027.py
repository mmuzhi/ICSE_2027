from collections import defaultdict
from typing import List

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int) # net out degree 
        for x, y in pairs: 
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1

        starts = []
        ends = []
        for node, d in degree.items():
            if d == 1:
                starts.append(node)
            elif d == -1:
                ends.append(node)
            elif d != 0:
                return []
        
        if (len(starts) == 1 and len(ends) == 1) or (len(starts) == 0 and len(ends) == 0):
            start_node = starts[0] if starts else next(iter(degree.keys())) if degree else None
        else:
            return []
        
        if start_node is None:
            return []
        
        ans = []

        def fn(x): 
            ans.append(x)
            while graph[x]:
                neighbor = graph[x].pop()
                fn(neighbor)
        
        fn(start_node)
        
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]