class Solution:
    def isPossible(self, n: int, edges: list[list[int]]) -> bool:
        if n == 0:
            return True
        
        graph = [[] for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            graph[a].append(b)
            graph[b].append(a)
        
        visited = [False] * n
        from collections import deque
        queue = deque()
        if n > 0:
            visited[0] = True
            queue.append(0)
            while queue:
                node = queue.popleft()
                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        queue.append(neighbor)
            connected = all(visited)
        else:
            connected = True
        
        if not connected:
            return False
        
        degrees = [len(graph[i]) for i in range(n)]
        odd_degrees = [i for i in range(n) if degrees[i] % 2 == 1]
        num_odd = len(odd_degrees)
        
        if num_odd == 0:
            return True
        elif num_odd == 2:
            return True
        elif num_odd == 4:
            return True
        else:
            return False