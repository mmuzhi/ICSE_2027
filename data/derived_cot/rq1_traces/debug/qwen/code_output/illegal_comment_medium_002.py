class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        n = len(roads) + 1
        adjacencyList = [[] for _ in range(n)]
        for road in roads:
            a, b = road
            adjacencyList[a].append(b)
            adjacencyList[b].append(a)
        
        res = [0]
        
        def dfs(i, parent):
            tot = 1
            for k in adjacencyList[i]:
                if k == parent:
                    continue
                child_tot = dfs(k, i)
                tot += child_tot
                if child_tot % seats == 0:
                    res[0] += child_tot // seats
                else:
                    res[0] += child_tot // seats + 1
            return tot
        
        dfs(0, None)
        return res[0]