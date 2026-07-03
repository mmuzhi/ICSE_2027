from typing import List

class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        visited = [0] * len(edges)
        max_cycle = -1
        for node in range(len(edges)):
            time = 1
            current = node
            while current >= 0:
                if visited[current] != 0:
                    if visited[current][0] == node:
                        max_cycle = max(max_cycle, time - visited[current][1])
                    break
                else:
                    visited[current] = [node, time]
                    time += 1
                    current = edges[current]
        return max_cycle