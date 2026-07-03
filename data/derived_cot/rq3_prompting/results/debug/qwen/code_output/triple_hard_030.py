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
                if start is None:
                    start = node
                else:
                    return []
            elif d == -1:
                if end is None:
                    end = node
                else:
                    return []
            elif d != 0:
                return []
        
        if start is None and end is None:
            if not graph:
                return []
            start = next(iter(graph.keys()))
        elif start is None or end is None:
            return []
        
        ans = []
        def dfs(node):
            while graph[node]:
                nxt = graph[node].pop()
                dfs(nxt)
            ans.append(node)
        
        dfs(start)
        ans.reverse()
        if len(ans) < 2:
            return []
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]