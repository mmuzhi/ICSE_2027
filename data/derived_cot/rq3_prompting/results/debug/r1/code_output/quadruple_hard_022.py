from typing import List
from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)          # net out-degree = out - in
        
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        # Find starting node: one with net out-degree == 1 (if exists)
        start = None
        for node in degree:
            if degree[node] == 1:
                start = node
                break
        if start is None:
            # Eulerian circuit: start from any node that appears in the graph
            start = next(iter(graph)) if graph else pairs[0][0]
        
        ans = []
        
        def dfs(node):
            while graph[node]:
                dfs(graph[node].pop())
            ans.append(node)
        
        dfs(start)
        ans.reverse()
        
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]