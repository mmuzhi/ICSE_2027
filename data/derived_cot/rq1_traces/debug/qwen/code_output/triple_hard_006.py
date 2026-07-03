from typing import List, defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        if not pairs:
            return []
        
        graph = defaultdict(list)
        degree = defaultdict(int)
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        total_edges = len(pairs)
        
        for node in degree:
            if degree[node] not in (-1, 0, 1):
                return []
        
        starts = [node for node, d in degree.items() if d == 1]
        ends = [node for node, d in degree.items() if d == -1]
        
        if len(starts) == 1 and len(ends) == 1:
            start_node = starts[0]
            end_node = ends[0]
        elif not starts and not ends:
            start_node = next(iter(degree.keys()))
        else:
            return []
        
        ans = []
        
        def fn(x):
            while graph[x]:
                y = graph[x].pop()
                fn(y)
            ans.append(x)
        
        fn(start_node)
        
        if len(ans) - 1 != total_edges:
            return []
        
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]