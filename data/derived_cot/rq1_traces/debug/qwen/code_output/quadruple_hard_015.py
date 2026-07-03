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
        
        non_zero = [node for node, d in degree.items() if d != 0]
        ans = []
        
        if not non_zero:
            if not graph:
                return []
            start = next(iter(graph.keys()))
            def dfs(x):
                while graph[x]:
                    y = graph[x].pop()
                    dfs(y)
                ans.append(x)
            dfs(start)
            ans.reverse()
            return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]
        else:
            if len(non_zero) != 2:
                return []
            node1, node2 = non_zero
            if degree[node1] == 1 and degree[node2] == -1:
                start = node1
            elif degree[node1] == -1 and degree[node2] == 1:
                start = node2
            else:
                return []
            def dfs(x):
                while graph[x]:
                    y = graph[x].pop()
                    dfs(y)
                ans.append(x)
            dfs(start)
            ans.reverse()
            return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]