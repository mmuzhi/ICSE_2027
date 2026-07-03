class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        # Build the graph
        graph = [[] for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            graph[a].append(b)
            graph[b].append(a)
        
        # Compute degrees
        degrees = [len(graph[i]) for i in range(n)]
        odd_degrees = [i for i in range(n) if degrees[i] % 2 == 1]
        if len(odd_degrees) != 0:
            return False
        
        # If there are no edges, then the graph is connected only if n <= 1.
        if sum(degrees) == 0:
            return n <= 1
        
        # Find a node with positive degree to start DFS
        start = None
        for i in range(n):
            if degrees[i] > 0:
                start = i
                break
        
        # Check connectivity (if there are edges)
        visited = [False] * n
        stack = [start]
        visited[start] = True
        while stack:
            node = stack.pop()
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    stack.append(neighbor)
        
        # We need to check that all nodes with positive degree are in the same connected component.
        total_positive_degree = sum(1 for i in range(n) if degrees[i] > 0)
        visited_positive = sum(1 for i in range(n) if visited[i] and degrees[i] > 0)
        if visited_positive != total_positive_degree:
            return False
        
        return True