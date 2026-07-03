class Solution:
    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        if not adjacentPairs:
            return [1]
        
        graph = {}
        for u, v in adjacentPairs:
            graph.setdefault(u, []).append(v)
            graph.setdefault(v, []).append(u)
        
        degrees = {node: len(graph[node]) for node in graph}
        endpoints = [node for node in graph if degrees[node] == 1]
        
        if len(endpoints) != 2:
            start = next(iter(graph.keys()))
        else:
            start = endpoints[0]
        
        seen = {start}
        stack = [start]
        ans = []
        prev = None
        while stack:
            node = stack.pop()
            ans.append(node)
            for neighbor in graph[node]:
                if neighbor == prev:
                    continue
                if neighbor not in seen:
                    seen.add(neighbor)
                    prev = node
                    stack.append(neighbor)
        
        return ans