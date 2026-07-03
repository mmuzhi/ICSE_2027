class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        n = len(roads) + 1
        adjacencyList = [[] for _ in range(n)]
        for a, b in roads:
            adjacencyList[a].append(b)
            adjacencyList[b].append(a)
        
        res = [0]
        visited = [0] * n
        visited[0] = 1
        
        def dfs(i, visited):
            visited[i] = 1
            tot = 1
            for k in adjacencyList[i]:
                if not visited[k]:
                    tot += dfs(k, visited)
            if i != 0:
                if tot % seats == 0:
                    res[0] += tot // seats
                else:
                    res[0] += tot // seats + 1
            return tot
        
        for i in adjacencyList[0]:
            if not visited[i]:
                dfs(i, visited)
        return res[0]