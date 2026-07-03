class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        n = len(roads) + 1
        adjacencyList = [[] for _ in range(n)]
        res = [0]
        
        for road in roads:
            u, v = road
            adjacencyList[u].append(v)
            adjacencyList[v].append(u)
        
        visited = [0] * n
        visited[0] = 1
        
        def dfs(i, visited):
            tot = 1
            for k in adjacencyList[i]:
                if visited[k]:
                    continue
                visited[k] = 1
                tot += dfs(k, visited)
            if tot % seats == 0:
                res[0] += tot // seats
            else:
                res[0] += tot // seats + 1
            return tot
        
        for i in range(1, n):
            if not visited[i]:
                dfs(i, visited)
                
        return res[0]