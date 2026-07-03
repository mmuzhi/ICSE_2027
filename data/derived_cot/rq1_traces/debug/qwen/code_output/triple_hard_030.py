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
        else:
            if degree:
                start = next(iter(degree.keys()))
            else:
                return []
        
        ans = []
        def dfs(x):
            while graph[x]:
                neighbor = graph[x].pop()
                dfs(neighbor)
            ans.append(x)
        
        dfs(start)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]