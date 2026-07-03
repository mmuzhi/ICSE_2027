class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        if not roads:
            return 0
        
        n_val = 0
        for road in roads:
            for node in road:
                if node > n_val:
                    n_val = node
        
        n_val += 1
        adjacencyList = [[] for _ in range(n_val)]
        
        for road in roads:
            u, v = road
            adjacencyList[u].append(v)
            adjacencyList[v].append(u)
        
        visited = [0] * n_val
        visited[0] = 1
        res = [0]
        
        def dfs(i):
            tot = 1
            for k in adjacencyList[i]:
                if visited[k]:
                    continue
                visited[k] = 1
                tot += dfs(k)
            buses = (tot + seats - 1) // seats
            res[0] += buses
            return tot
        
        for neighbor in adjacencyList[0]:
            if not visited[neighbor]:
                dfs(neighbor)
                
        return res[0]