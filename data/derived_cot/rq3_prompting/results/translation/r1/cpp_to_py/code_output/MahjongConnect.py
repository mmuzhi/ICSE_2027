import random
from typing import List, Tuple

class MahjongConnect:
    def __init__(self, board_size: Tuple[int, int], icons: List[str]):
        self.BOARD_SIZE = board_size
        self.ICONS = icons
        self.board = self.create_board()

    def create_board(self) -> List[List[str]]:
        rows, cols = self.BOARD_SIZE
        board = [['' for _ in range(cols)] for _ in range(rows)]
        for i in range(rows):
            for j in range(cols):
                board[i][j] = random.choice(self.ICONS)
        return board

    def is_valid_move(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        x1, y1 = pos1
        x2, y2 = pos2
        rows, cols = self.BOARD_SIZE

        # check bounds
        if not (0 <= x1 < rows and 0 <= y1 < cols and 0 <= x2 < rows and 0 <= y2 < cols):
            return False
        # non‑same position
        if pos1 == pos2:
            return False
        # must have same icon
        if self.board[x1][y1] != self.board[x2][y2]:
            return False
        # check path
        return self.has_path(pos1, pos2)

    def has_path(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        visited = set()
        stack = [pos1]

        while stack:
            cur = stack.pop()
            if cur == pos2:
                return True
            if cur in visited:
                continue
            visited.add(cur)
            x, y = cur
            # four directions
            for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0)):
                nx, ny = x + dx, y + dy
                if 0 <= nx < self.BOARD_SIZE[0] and 0 <= ny < self.BOARD_SIZE[1]:
                    if (nx, ny) not in visited and self.board[nx][ny] == self.board[x][y]:
                        stack.append((nx, ny))
        return False

    def remove_icons(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> None:
        self.board[pos1[0]][pos1[1]] = ' '
        self.board[pos2[0]][pos2[1]] = ' '

    def is_game_over(self) -> bool:
        for row in self.board:
            for icon in row:
                if icon != ' ':
                    return False
        return True