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

        start = None
        for k, d in degree.items():
            if d == 1:
                start = k
                break
        if start is None:
            # If no node with net out-degree 1, pick any node from graph
            start = next(iter(graph)) if graph else pairs[0][0]

        ans = []

        def fn(x):
            """Return Eulerian path via dfs."""
            while graph[x]:
                fn(graph[x].pop())
            ans.append(x)

        fn(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]