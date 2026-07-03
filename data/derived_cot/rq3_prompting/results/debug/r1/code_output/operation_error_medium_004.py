from typing import List

class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        n = len(roads) + 1
        adjacencyList = [[] for _ in range(n)]
        for u, v in roads:
            adjacencyList[u].append(v)
            adjacencyList[v].append(u)
        
        visited = [0] * n
        visited[0] = 1
        res = [0]
        
        def dfs(node: int, visited: List[int]) -> int:
            if visited[node]:
                return 0
            visited[node] = 1
            people = 1
            for neighbor in adjacencyList[node]:
                people += dfs(neighbor, visited)
            # cars needed to move this subtree's people to the parent
            res[0] += (people + seats - 1) // seats
            return people
        
        for neighbor in adjacencyList[0]:
            dfs(neighbor, visited)
        
        return res[0]