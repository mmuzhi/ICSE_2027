class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        neighbors = [set() for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            neighbors[a].add(b)
            neighbors[b].add(a)
        
        oddDegreesNodes = [i for i in range(n) if (len(neighbors[i]) % 2 == 1)]
        numOdd = len(oddDegreesNodes)
        
        if numOdd not in [0, 2]:
            return False
        
        visited = [False] * n
        stack = []
        nonIsolated = set()
        for i in range(n):
            if len(neighbors[i]) > 0:
                nonIsolated.add(i)
        
        if not nonIsolated:
            return True
        
        stack.append(next(iter(nonIsolated)))
        while stack:
            node = stack.pop()
            if not visited[node]:
                visited[node] = True
                for neighbor in neighbors[node]:
                    if not visited[neighbor]:
                        stack.append(neighbor)
        
        for node in nonIsolated:
            if not visited[node]:
                return False
        
        return True