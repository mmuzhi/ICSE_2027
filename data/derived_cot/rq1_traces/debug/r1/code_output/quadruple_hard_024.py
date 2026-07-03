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
        # Find node with net out degree 1 (start of Eulerian path)
        for k in degree:
            if degree[k] == 1:
                x = k
                break
        # If no such node, find any node with outgoing edges (Eulerian circuit)
        if x is None:
            for k in graph:
                if graph[k]:
                    x = k
                    break

        ans = []
        def dfs(node):
            while graph[node]:
                next_node = graph[node].pop()
                dfs(next_node)
            ans.append(node)
        
        dfs(x)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]