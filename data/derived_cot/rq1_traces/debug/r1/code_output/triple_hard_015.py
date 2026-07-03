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

        x = None
        # Find the node with net out degree 1
        for k in degree:
            if degree[k] == 1:
                x = k
                break
        # If no such node, find any node with outgoing edges
        if x is None:
            for k in graph:
                if graph[k]:
                    x = k
                    break

        ans = []

        def fn(node):
            """Return Eulerian path via dfs."""
            while graph[node]:
                next_node = graph[node].pop()
                fn(next_node)
            ans.append(node)

        fn(x)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]