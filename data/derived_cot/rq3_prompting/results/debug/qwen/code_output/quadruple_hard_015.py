from collections import defaultdict, List

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
        else:
            start = next(iter(degree.keys()))
        
        ans = []
        
        def dfs(u):
            ans.append(u)
            while graph[u]:
                v = graph[u].pop()
                dfs(v)
        
        dfs(start)
        
        res = []
        for i in range(len(ans) - 1):
            res.append([ans[i], ans[i+1]])
        
        return res