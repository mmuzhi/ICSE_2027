from typing import List

class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        graph = [[] for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            graph[a].append(b)
            graph[b].append(a)
        
        degree = [len(graph[i]) for i in range(n)]
        
        visited = [False] * n
        stack = [0]
        visited[0] = True
        while stack:
            node = stack.pop()
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    stack.append(neighbor)
        
        if not all(visited):
            return False
        
        odd_count = sum(1 for d in degree if d % 2 == 1)
        return odd_count == 0 or odd_count == 2