from typing import List
from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)  # net out-degree
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        # Find start node: node with outdegree - indegree = 1, else any node with non-zero degree
        start = None
        for k in degree:
            if degree[k] == 1:
                start = k
                break
        if start is None:
            start = next(iter(graph))  # any node in graph
        
        ans = []
        
        def dfs(node):
            while graph[node]:
                dfs(graph[node].pop())
            ans.append(node)
        
        dfs(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]