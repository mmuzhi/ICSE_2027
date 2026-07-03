from typing import List
from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        x = None
        for k in degree:
            if degree[k] == 1:
                x = k
                break
        if x is None:
            for k in graph:
                if graph[k]:
                    x = k
                    break
        
        ans = []
        
        def fn(x):
            while graph[x]:
                fn(graph[x].pop())
            ans.append(x)
        
        fn(x)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]