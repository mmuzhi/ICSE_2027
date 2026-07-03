class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        visited = [0] * n
        max_cycle = -1
        for i in range(n):
            if not visited[i]:
                distance = {}
                current = i
                length = 0
                while current != -1 and not visited[current]:
                    visited[current] = 1
                    distance[current] = length
                    length += 1
                    current = edges[current]
                if current != -1 and current in distance:
                    cycle_length = length - distance[current]
                    max_cycle = max(max_cycle, cycle_length)
        return max_cycle