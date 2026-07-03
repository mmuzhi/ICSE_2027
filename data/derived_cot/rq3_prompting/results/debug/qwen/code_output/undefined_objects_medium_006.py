from collections import deque

class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        rev_graph = [[] for _ in range(n)]
        for edge in edges:
            src, dest = edge[0], edge[1]
            rev_graph[dest].append(src)
        
        ans = [set() for _ in range(n)]
        
        for i in range(n):
            visited = set()
            queue = deque([i])
            visited.add(i)
            while queue:
                node = queue.popleft()
                for neighbor in rev_graph[node]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
            visited.discard(i)
            ans[i] = visited
        
        return [sorted(list(s)) for s in ans]