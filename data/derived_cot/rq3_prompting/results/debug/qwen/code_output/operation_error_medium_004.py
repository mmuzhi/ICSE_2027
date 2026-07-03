class Solution:
    def minimumFuelCost(self, roads: List[List[int]], seats: int) -> int:
        if not roads:
            return 0
        nodes = set()
        for road in roads:
            nodes.add(road[0])
            nodes.add(road[1])
        max_node = max(nodes) if nodes else 0
        adjacencyList = [[] for _ in range(max_node + 1)]
        for road in roads:
            u, v = road
            adjacencyList[u].append(v)
            adjacencyList[v].append(u)
        
        res = [0]
        
        def dfs(i, parent):
            tot = 1
            for k in adjacencyList[i]:
                if k == parent:
                    continue
                child_people = dfs(k, i)
                tot += child_people
                res[0] += (child_people + seats - 1) // seats
            return tot
        
        dfs(0, -1)
        return res[0]