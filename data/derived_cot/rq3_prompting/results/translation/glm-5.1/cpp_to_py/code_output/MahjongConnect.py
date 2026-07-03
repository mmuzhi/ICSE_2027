import random


class MahjongConnect:
    def __init__(self, boardSize, icons):
        self.BOARD_SIZE = boardSize
        self.ICONS = icons
        self.board = self.create_board()

    def create_board(self):
        newBoard = []
        for i in range(self.BOARD_SIZE[0]):
            row = []
            for j in range(self.BOARD_SIZE[1]):
                row.append(self.ICONS[random.randint(0, len(self.ICONS) - 1)])
            newBoard.append(row)
        return newBoard

    def is_valid_move(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2

        if not (0 <= x1 < self.BOARD_SIZE[0] and 0 <= y1 < self.BOARD_SIZE[1] and
                0 <= x2 < self.BOARD_SIZE[0] and 0 <= y2 < self.BOARD_SIZE[1]):
            return False

        if pos1 == pos2:
            return False

        if self.board[x1][y1] != self.board[x2][y2]:
            return False

        return self.has_path(pos1, pos2)

    def has_path(self, pos1, pos2):
        visited = set()
        stack = [pos1]

        while stack:
            currentPos = stack.pop()

            if currentPos == pos2:
                return True

            if currentPos in visited:
                continue

            visited.add(currentPos)
            x, y = currentPos

            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                newX, newY = x + dx, y + dy
                if 0 <= newX < self.BOARD_SIZE[0] and 0 <= newY < self.BOARD_SIZE[1]:
                    if (newX, newY) not in visited and self.board[newX][newY] == self.board[x][y]:
                        stack.append((newX, newY))

        return False

    def remove_icons(self, pos1, pos2):
        self.board[pos1[0]][pos1[1]] = ' '
        self.board[pos2[0]][pos2[1]] = ' '

    def is_game_over(self):
        for row in self.board:
            if any(icon != ' ' for icon in row):
                return False
        return True