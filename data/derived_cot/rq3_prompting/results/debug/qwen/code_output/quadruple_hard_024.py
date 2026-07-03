from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        start = None
        for node in degree:
            if degree[node] == 1:
                start = node
                break
        
        if start is None and graph:
            start = next(iter(graph.keys()))
        
        ans = []
        
        def fn(x):
            while graph[x]:
                neighbor = graph[x].pop()
                fn(neighbor)
            ans.append(x)
        
        if graph:
            fn(start)
        else:
            return []
        
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]