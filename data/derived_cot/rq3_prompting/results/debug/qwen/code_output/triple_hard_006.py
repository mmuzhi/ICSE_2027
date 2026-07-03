from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        
        for x, y in pairs:
            graph[x].append(y)
            graph[y].append(x)
            degree[x] += 1
            degree[y] += 1
            
        if not graph:
            return []
        
        odd_degree_nodes = [node for node in degree if degree[node] % 2 != 0]
        
        if len(odd_degree_nodes) == 0:
            start = next(iter(graph))
        elif len(odd_degree_nodes) == 2:
            start = odd_degree_nodes[0]
        else:
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