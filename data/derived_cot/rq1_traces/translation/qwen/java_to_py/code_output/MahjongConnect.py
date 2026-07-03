import random
from typing import List, Tuple

class MahjongConnect:
    def __init__(self, board_size: Tuple[int, int], icons: List[str]):
        self.board_size = board_size
        self.icons = icons
        self.board = self._create_board()

    def _create_board(self) -> List[List[str]]:
        board = [['' for _ in range(self.board_size[1])] for _ in range(self.board_size[0])]
        for i in range(self.board_size[0]):
            for j in range(self.board_size[1]):
                board[i][j] = random.choice(self.icons)
        return board

    def is_valid_position(self, x: int, y: int) -> bool:
        return (0 <= x < self.board_size[0]) and (0 <= y < self.board_size[1])

    def is_valid_move(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        x1, y1 = pos1
        x2, y2 = pos2

        if not self.is_valid_position(x1, y1) or not self.is_valid_position(x2, y2):
            return False

        if x1 == x2 and y1 == y2:
            return False

        if self.board[x1][y1] != self.board[x2][y2]:
            return False

        return self.has_path(pos1, pos2)

    def has_path(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> bool:
        start_x, start_y = pos1
        target_x, target_y = pos2

        if not self.is_valid_position(start_x, start_y) or not self.is_valid_position(target_x, target_y):
            return False

        visited = [[False for _ in range(self.board_size[1])] for _ in range(self.board_size[0])]
        return self._dfs(start_x, start_y, target_x, target_y, visited)

    def _dfs(self, x: int, y: int, target_x: int, target_y: int, visited: List[List[bool]]) -> bool:
        if x == target_x and y == target_y:
            return True

        if visited[x][y]:
            return False

        visited[x][y] = True

        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if self.is_valid_position(nx, ny) and not visited[nx][ny] and self.board[nx][ny] == self.board[x][y]:
                if self._dfs(nx, ny, target_x, target_y, visited):
                    return True

        return False

    def remove_icons(self, pos1: Tuple[int, int], pos2: Tuple[int, int]) -> None:
        x1, y1 = pos1
        x2, y2 = pos2
        self.board[x1][y1] = ''
        self.board[x2][y2] = ''

    def is_game_over(self) -> bool:
        for i in range(self.board_size[0]):
            for j in range(self.board_size[1]):
                if self.board[i][j] != '':
                    return False
        return True

def main():
    board_size = (4, 4)
    icons = ['a', 'b', 'c']
    game = MahjongConnect(board_size, icons)
    print(game.is_valid_move((0, 0), (1, 0)))
    game.remove_icons((0, 0), (1, 0))
    print(game.is_game_over())

if __name__ == "__main__":
    main()