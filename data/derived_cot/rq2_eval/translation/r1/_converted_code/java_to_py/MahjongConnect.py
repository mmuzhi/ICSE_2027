import random

class MahjongConnect:

    def __init__(self, BOARD_SIZE, ICONS):
        self.BOARD_SIZE = BOARD_SIZE
        self.ICONS = ICONS
        self.board = self.create_board()

    def create_board(self):
        rows = self.BOARD_SIZE[0]
        cols = self.BOARD_SIZE[1]
        board = [['' for _ in range(cols)] for _ in range(rows)]
        for i in range(rows):
            for j in range(cols):
                board[i][j] = random.choice(self.ICONS)
        return board

    def isValidPosition(self, x, y):
        return 0 <= x < self.BOARD_SIZE[0] and 0 <= y < self.BOARD_SIZE[1]

    def is_valid_move(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2
        if not (self.isValidPosition(x1, y1) and self.isValidPosition(x2, y2)):
            return False
        if (x1, y1) == (x2, y2):
            return False
        if self.board[x1][y1] != self.board[x2][y2]:
            return False
        return self.has_path(pos1, pos2)

    def has_path(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2
        if not (self.isValidPosition(x1, y1) and self.isValidPosition(x2, y2)):
            return False
        visited = [[False for _ in range(self.BOARD_SIZE[1])] for _ in range(self.BOARD_SIZE[0])]
        return self.dfs(x1, y1, pos2, visited)

    def dfs(self, x, y, target, visited):
        if x == target[0] and y == target[1]:
            return True
        if visited[x][y]:
            return False
        visited[x][y] = True
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        for dx, dy in directions:
            new_x = x + dx
            new_y = y + dy
            if self.isValidPosition(new_x, new_y) and (not visited[new_x][new_y]) and (self.board[new_x][new_y] == self.board[x][y]):
                if self.dfs(new_x, new_y, target, visited):
                    return True
        return False

    def remove_icons(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2
        self.board[x1][y1] = ' '
        self.board[x2][y2] = ' '

    def is_game_over(self):
        for i in range(self.BOARD_SIZE[0]):
            for j in range(self.BOARD_SIZE[1]):
                if self.board[i][j] != ' ':
                    return False
        return True
if __name__ == '__main__':
    board_size = [4, 4]
    icons = ['a', 'b', 'c']
    mc = MahjongConnect(board_size, icons)
    print(mc.isValidMove([0, 0], [1, 0]))
    mc.removeIcons([0, 0], [1, 0])
    print(mc.isGameOver())