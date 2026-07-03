from typing import List
from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)  # net out degree
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1

        x = None
        for k in degree:
            if degree[k] == 1:
                x = k
                break
        # If no node with degree 1, find a node with outgoing edges
        if x is None:
            for k in graph:
                if graph[k]:
                    x = k
                    break

        ans = []

        def fn(x):
            """Return Eulerian path via dfs."""
            while graph[x]:
                next_node = graph[x].pop()
                fn(next_node)
            ans.append(x)

        fn(x)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]