from collections import deque
from typing import List

class Solution:
    def countSubgraphsForEachDiameter(self, n: int, edges: List[List[int]]) -> List[int]:
        # Build graph
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u-1].append(v-1)
            adj[v-1].append(u-1)
        
        # ans[0] for diameter 0, ans[1] for diameter 1, ... up to diameter n-1.
        ans = [0] * n
        
        # Iterate over all non-empty subsets of nodes
        # We use bitmask from 1 to (1<<n)-1
        for bitmask in range(1, 1 << n):
            # Get the list of nodes in this subset
            nodes = []
            for i in range(n):
                if bitmask & (1 << i):
                    nodes.append(i)
            k = len(nodes)
            # Skip single-node subgraphs
            if k == 1:
                continue
            # Check connectivity of the subset
            if not self.is_connected(nodes, adj):
                continue
            
            # Compute the diameter of the subset
            diameter = self.compute_diameter(nodes, adj)
            if diameter < 1 or diameter >= n:
                continue
            ans[diameter] += 1
        
        # Return ans[1:] to skip diameter 0
        return ans[1:]
    
    def is_connected(self, nodes, adj):
        if not nodes:
            return True
        start = nodes[0]
        visited = set([start])
        queue = deque([start])
        while queue:
            node = queue.popleft()
            for neighbor in adj[node]:
                if neighbor in nodes and neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        return len(visited) == len(nodes)
    
    def compute_diameter(self, nodes, adj):
        sub_adj = {}
        for node in nodes:
            sub_adj[node] = [neighbor for neighbor in adj[node] if neighbor in nodes]
        
        max_diameter = 0
        for node in nodes:
            dist = {}
            for n_node in nodes:
                dist[n_node] = -1
            dist[node] = 0
            queue = deque([node])
            while queue:
                cur = queue.popleft()
                for neighbor in sub_adj[cur]:
                    if dist[neighbor] == -1:
                        dist[neighbor] = dist[cur] + 1
                        queue.append(neighbor)
            current_max = max(dist.values())
            if current_max > max_diameter:
                max_diameter = current_max
        
        return max_diameter