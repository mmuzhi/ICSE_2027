from collections import defaultdict
from typing import List

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)  # net out degree
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        # Find start node for Eulerian path
        start = None
        for k in degree:
            if degree[k] == 1:
                start = k
                break
        if start is None:
            start = next(iter(graph))
        
        ans = []
        def fn(node):
            while graph[node]:
                fn(graph[node].pop())
            ans.append(node)
        
        fn(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]