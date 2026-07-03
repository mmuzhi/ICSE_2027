import random
from typing import List, Tuple, Set

class MahjongConnect:
    def __init__(self, board_size: Tuple[int, int], icons: List[str]):
        self.board_size = board_size
        self.icons = icons
        self.board: List[List[str]] = self.create_board()

    def create_board(self) -> List[List[str]]:
        width, height = self.board_size
        new_board = [['' for _ in range(width)] for _ in range(height)]
        for i in range(height):
            for j in range(width):
                new_board[i][j] = random.choice(self.icons)
        return new_board

    def is_valid_move(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        x1, y1 = pos1
        x2, y2 = pos2

        # Check if positions are within bounds
        if not (0 <= x1 < self.board_size[0] and 0 <= y1 < self.board_size[1] and
                0 <= x2 < self.board_size[0] and 0 <= y2 < self.board_size[1]):
            return False

        # Check if positions are the same
        if pos1 == pos2:
            return False

        # Check if icons match
        if self.board[x1][y1] != self.board[x2][y2]:
            return False

        # Check if there's a path between them
        return self.has_path(pos1, pos2)

    def has_path(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        start_x, start_y = pos1
        end_x, end_y = pos2

        # If start and end positions are the same, return True (though is_valid_move checks this)
        if start_x == end_x and start_y == end_y:
            return True

        stack: List[Tuple[int, int]] = [(start_x, start_y)]
        visited: Set[Tuple[int, int]] = {(start_x, start_y)}
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        while stack:
            x, y = stack.pop()
            if (x, y) == (end_x, end_y):
                return True

            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if (0 <= nx < self.board_size[0] and 0 <= ny < self.board_size[1] and
                        (nx, ny) not in visited and self.board[nx][ny] == self.board[x][y]):
                    visited.add((nx, ny))
                    stack.append((nx, ny))

        return False

    def remove_icons(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> None:
        x1, y1 = pos1
        x2, y2 = pos2
        self.board[x1][y1] = ' '
        self.board[x2][y2] = ' '

    def is_game_over(self) -> bool:
        for row in self.board:
            if any(cell != ' ' for cell in row):
                return False
        return True