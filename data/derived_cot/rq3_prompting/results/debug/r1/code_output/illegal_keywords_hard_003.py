from collections import deque
from typing import List

class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        if not edges:
            return 1.0 if target == 1 else 0.0

        # Build adjacency list
        adj = {}
        for a, b in edges:
            adj.setdefault(a, []).append(b)
            adj.setdefault(b, []).append(a)

        visited = [0] * (n + 1)
        q = deque()
        q.append([1, 1.0])                # [node, probability]

        for _ in range(t):
            level_size = len(q)
            for _ in range(level_size):
                node, prob = q.popleft()

                # Count unvisited neighbors
                cnt = 0
                for nb in adj[node]:
                    if visited[nb] == 0:
                        cnt += 1

                # If frog is stuck at the target, probability stays the same
                if node == target and cnt == 0:
                    return prob

                # Already visited? (shouldn't happen, but safe)
                if visited[node] != 0:
                    continue

                visited[node] = 1

                # Distribute probability to unvisited children
                for nb in adj[node]:
                    if visited[nb] == 0:
                        q.append([nb, prob * (1.0 / cnt)])

        # After t seconds, check remaining nodes
        for node, prob in q:
            if node == target:
                return prob

        return 0.0