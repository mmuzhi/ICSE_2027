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
        for node, d in degree.items():
            if d == 1:
                start = node
            elif d == -1:
                end = node
            elif d != 0:
                return []
        
        if start is None and end is None:
            start = next(iter(degree.keys()))
        elif start is None:
            return []
        elif end is None:
            return []
        
        ans = []
        
        def dfs(x):
            while graph[x]:
                y = graph[x].pop()
                dfs(y)
            ans.append(x)
        
        dfs(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]