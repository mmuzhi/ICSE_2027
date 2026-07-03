class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        graph = [[] for _ in range(n)]
        degree = [0] * n
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            graph[a].append(b)
            graph[b].append(a)
            degree[a] += 1
            degree[b] += 1
        
        visited = [False] * n
        stack = [0]
        visited[0] = True
        count_visited = 1
        while stack:
            node = stack.pop()
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    count_visited += 1
                    stack.append(neighbor)
        
        if count_visited != n:
            return False
        
        oddDegreesNodes = [i for i in range(n) if degree[i] % 2 == 1]
        numOdd = len(oddDegreesNodes)
        return numOdd == 0 or numOdd == 2