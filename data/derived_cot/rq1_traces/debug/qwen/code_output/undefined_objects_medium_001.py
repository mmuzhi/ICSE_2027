from collections import deque, defaultdict

class Solution:
    def reachableNodes(self, n: int, edges: List[List[int]], restricted: List[int]) -> int:
        adj_list = defaultdict(list)
        for u, v in edges:
            adj_list[u].append(v)
            adj_list[v].append(u)
        
        visited = set(restricted)
        if 0 in visited:
            return 0
        
        que = deque([0])
        visited.add(0)
        count = 1
        
        while que:
            cur = que.popleft()
            for neighbor in adj_list[cur]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    count += 1
                    que.append(neighbor)
        
        return count