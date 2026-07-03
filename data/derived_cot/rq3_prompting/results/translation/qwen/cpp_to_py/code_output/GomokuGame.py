class GomokuGame:
    def __init__(self, board_size):
        self.board_size = board_size
        self.board = [[' ' for _ in range(board_size)] for _ in range(board_size)]
        self.current_player = 'X'

    def make_move(self, row, col):
        if 0 <= row < self.board_size and 0 <= col < self.board_size and self.board[row][col] == ' ':
            self.board[row][col] = self.current_player
            self.current_player = 'O' if self.current_player == 'X' else 'X'
            return True
        return False

    def check_winner(self):
        directions = [(0, 1), (1, 0), (1, 1), (1, -1)]
        for i in range(self.board_size):
            for j in range(self.board_size):
                if self.board[i][j] != ' ':
                    for dx, dy in directions:
                        if self._check_five_in_a_row(i, j, dx, dy):
                            return self.board[i][j]
        return None

    def get_board(self):
        return self.board

    def _check_five_in_a_row(self, row, col, dx, dy):
        count = 1
        symbol = self.board[row][col]
        for step in range(1, 5):
            new_row = row + dx * step
            new_col = col + dy * step
            if (new_row < 0 or new_row >= self.board_size or 
                new_col < 0 or new_col >= self.board_size or 
                self.board[new_row][new_col] != symbol):
                return False
            count += 1
        return count == 5