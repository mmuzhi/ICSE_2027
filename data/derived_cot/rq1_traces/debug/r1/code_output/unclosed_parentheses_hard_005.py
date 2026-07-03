class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        visited = [0] * n
        max_cycle = -1
        for i in range(n):
            if visited[i] == 0:
                current = i
                length = 0
                path_set = set()
                index_map = {}
                while current != -1 and visited[current] == 0:
                    visited[current] = 1
                    index_map[current] = length
                    length += 1
                    path_set.add(current)
                    current = edges[current]
                if current != -1 and current in path_set:
                    cycle_length = length - index_map[current]
                    max_cycle = max(max_cycle, cycle_length)
        return max_cycle