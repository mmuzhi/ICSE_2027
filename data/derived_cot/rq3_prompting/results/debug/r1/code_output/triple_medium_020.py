from typing import List

class Solution:
    def restoreArray(self, adjacentPairs: List[List[int]]) -> List[int]:
        graph = {}
        for u, v in adjacentPairs:
            graph.setdefault(u, []).append(v)
            graph.setdefault(v, []).append(u)
        
        # Find a starting node (one with degree 1)
        start = next(x for x in graph if len(graph[x]) == 1)
        ans = []
        seen = set()
        stack = [start]
        while stack:
            n = stack.pop()
            ans.append(n)
            seen.add(n)
            for nn in graph[n]:
                if nn not in seen:
                    stack.append(nn)
        return ans