from typing import List
from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int) # net out degree 
        for u, v in pairs: 
            graph[u].append(v)
            degree[u] += 1
            degree[v] -= 1
                
        start = pairs[0][0]
        for k in degree: 
            if degree[k] == 1: 
                start = k
                break 
                
        ans = []

        def fn(node): 
            """Return Eulerian path via dfs."""
            while graph[node]: fn(graph[node].pop()) 
            ans.append(node)
        
        fn(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]