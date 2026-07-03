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
        end = None
        for node in degree:
            d = degree[node]
            if d == 1:
                if start is not None:
                    return []
                start = node
            elif d == -1:
                if end is not None:
                    return []
                end = node
            elif d != 0:
                return []
        
        if start is None and end is None:
            for node in graph:
                if graph[node]:
                    start = node
                    break
            if start is None:
                return []
        
        ans = []
        
        def fn(x):
            while graph[x]:
                y = graph[x].pop()
                fn(y)
            ans.append(x)
        
        fn(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]