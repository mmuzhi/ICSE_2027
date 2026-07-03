from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        start_node = None
        for k in degree:
            if degree[k] == 1:
                start_node = k
                break
        
        if start_node is None and graph:
            start_node = next(iter(graph.keys()))
        elif not graph:
            return []
        
        ans = []
        
        def fn(x):
            while graph[x]:
                fn(graph[x].pop())
            ans.append(x)
        
        fn(start_node)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]