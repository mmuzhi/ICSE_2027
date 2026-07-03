import random

class MahjongConnect:
    def __init__(self, board_size, icons):
        self.board_size = board_size
        self.icons = icons
        self.board = self.create_board()

    def create_board(self):
        board = [['' for _ in range(self.board_size[1])] for _ in range(self.board_size[0])]
        for i in range(self.board_size[0]):
            for j in range(self.board_size[1]):
                board[i][j] = random.choice(self.icons)
        return board

    def is_valid_position(self, x, y):
        return 0 <= x < self.board_size[0] and 0 <= y < self.board_size[1]

    def is_valid_move(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2

        if not self.is_valid_position(x1, y1) or not self.is_valid_position(x2, y2):
            return False

        if x1 == x2 and y1 == y2:
            return False

        if self.board[x1][y1] != self.board[x2][y2]:
            return False

        return self.has_path(pos1, pos2)

    def has_path(self, pos1, pos2, visited=None):
        if visited is None:
            visited = [[False for _ in range(self.board_size[1])] for _ in range(self.board_size[0])]

        x1, y1 = pos1
        x2, y2 = pos2

        if not self.is_valid_position(x1, y1) or not self.is_valid_position(x2, y2):
            return False

        if x1 == x2 and y1 == y2:
            return True

        visited[x1][y1] = True

        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        for dx, dy in directions:
            nx, ny = x1 + dx, y1 + dy
            if self.is_valid_position(nx, ny) and not visited[nx][ny] and self.board[nx][ny] == self.board[x1][y1]:
                if self.has_path((nx, ny), pos2, visited):
                    return True

        return False

    def remove_icons(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2
        self.board[x1][y1] = ' '
        self.board[x2][y2] = ' '

    def is_game_over(self):
        for i in range(self.board_size[0]):
            for j in range(self.board_size[1]):
                if self.board[i][j] != ' ':
                    return False
        return True

if __name__ == '__main__':
    board_size = [4, 4]
    icons = ["a", "b", "c"]
    mc = MahjongConnect(board_size, icons)
    print(mc.is_valid_move([0, 0], [1, 0]))
    mc.remove_icons([0, 0], [1, 0])
    print(mc.is_game_over())