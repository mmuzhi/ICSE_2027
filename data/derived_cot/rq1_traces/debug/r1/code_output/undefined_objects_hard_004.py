from typing import List
from collections import deque

class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:
        def get_neighbors(state):
            neighbors = []
            r, c = 0, 0
            for i in range(2):
                for j in range(3):
                    if state[i][j] == 0:
                        r, c = i, j
            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
            for dr, dc in directions:
                new_r, new_c = r + dr, c + dc
                if 0 <= new_r < 2 and 0 <= new_c < 3:
                    new_state = [row[:] for row in state]
                    new_state[r][c], new_state[new_r][new_c] = new_state[new_r][new_c], new_state[r][c]
                    neighbors.append(new_state)
            return neighbors

        target = [[1, 2, 3], [4, 5, 0]]
        initial = [row[:] for row in board]
        queue = deque([(initial, 0)])
        visited = set()
        visited.add(tuple(map(tuple, initial)))

        while queue:
            current, moves = queue.popleft()
            if current == target:
                return moves
            for neighbor in get_neighbors(current):
                neighbor_tuple = tuple(map(tuple, neighbor))
                if neighbor_tuple not in visited:
                    visited.add(neighbor_tuple)
                    queue.append((neighbor, moves + 1))
        return -1