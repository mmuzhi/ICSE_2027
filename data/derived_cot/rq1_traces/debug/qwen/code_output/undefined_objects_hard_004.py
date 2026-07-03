from collections import deque
from typing import List

class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:
        def get_neighbors(board):
            neighbors = []
            r, c = 0, 0
            for i in range(2):
                for j in range(3):
                    if board[i][j] == 0:
                        r, c = i, j
            for di, dj in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                ni, nj = r + di, c + dj
                if 0 <= ni < 2 and 0 <= nj < 3:
                    new_board = [row[:] for row in board]
                    new_board[r][c], new_board[ni][nj] = new_board[ni][nj], 0
                    neighbors.append(new_board)
            return neighbors

        queue = deque()
        queue.append((board, 0))
        seen = set()
        seen.add(tuple(tuple(row) for row in board))

        while queue:
            board, moves = queue.popleft()
            if board == [[1, 2, 3], [4, 5, 0]]:
                return moves
            for neighbor in get_neighbors(board):
                if tuple(tuple(row) for row in neighbor) not in seen:
                    seen.add(tuple(tuple(row) for row in neighbor))
                    queue.append((neighbor, moves + 1))
        return -1