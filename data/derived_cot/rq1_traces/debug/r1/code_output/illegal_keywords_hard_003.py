from queue import Queue
from typing import List

class Solution:
    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        if not edges:
            return 1.0 if target == 1 else 0.0

        adj = {}
        for u, v in edges:
            adj.setdefault(u, []).append(v)
            adj.setdefault(v, []).append(u)
        
        visited = [0] * (n + 1)
        q = Queue()
        q.put((1, 1.0))

        for _ in range(t):
            level_size = q.qsize()
            for __ in range(level_size):
                current, prob = q.get()
                count = 0
                for neighbor in adj.get(current, []):
                    if not visited[neighbor]:
                        count += 1
                if current == target and count == 0:
                    return prob
                if visited[current]:
                    continue
                visited[current] = 1
                if count == 0:
                    q.put((current, prob))
                    continue
                new_prob = prob / count
                for neighbor in adj.get(current, []):
                    if not visited[neighbor]:
                        q.put((neighbor, new_prob))
        
        while not q.empty():
            current, prob = q.get()
            if current == target:
                return prob
        
        return 0.0