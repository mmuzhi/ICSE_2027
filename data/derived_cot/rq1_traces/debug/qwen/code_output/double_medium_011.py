from collections import deque

class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        graph = [[] for _ in range(n)]
        indegrees = [0] * n
        
        for edge in edges:
            u, v = edge
            graph[u].append(v)
            indegrees[v] += 1
        
        ans = [set() for _ in range(n)]
        q = deque()
        
        for i in range(n):
            if indegrees[i] == 0:
                q.append(i)
                
        while q:
            cur = q.popleft()
            for v in graph[cur]:
                ans[v].add(cur)
                ans[v].update(ans[cur])
                indegrees[v] -= 1
                if indegrees[v] == 0:
                    q.append(v)
                    
        result = []
        for s in ans:
            result.append(sorted(list(s)))
            
        return result