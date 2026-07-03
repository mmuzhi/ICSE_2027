class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        adjacencyList = [[] for _ in range(len(roads) + 1)]
        res = 0
        for a, b in roads:
            adjacencyList[a].append(b)
            adjacencyList[b].append(a)
        visited = [False] * (len(roads) + 1)
        visited[0] = True
        
        def dfs(node):
            nonlocal res
            total_people = 1
            for neighbor in adjacencyList[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    total_people += dfs(neighbor)
            if node != 0:
                res += (total_people + seats - 1) // seats
            return total_people
        
        for neighbor in adjacencyList[0]:
            if not visited[neighbor]:
                visited[neighbor] = True
                dfs(neighbor)
        
        return res