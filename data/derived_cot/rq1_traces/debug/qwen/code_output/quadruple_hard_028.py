from collections import defaultdict
from typing import List

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        start_candidates = [k for k in degree if degree[k] == 1]
        if not start_candidates:
            if graph:
                x = next(iter(graph.keys()))
            else:
                return []
        else:
            x = start_candidates[0]
        
        def fn(x):
            while graph[x]:
                nxt = graph[x].pop()
                fn(nxt)
            ans.append(x)
        
        ans = []
        fn(x)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]