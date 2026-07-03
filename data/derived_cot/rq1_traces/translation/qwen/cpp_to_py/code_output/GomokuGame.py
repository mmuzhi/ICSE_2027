class GomokuGame:
    def __init__(self, board_size):
        self.board_size = board_size
        self.board = [[' ' for _ in range(board_size)] for _ in range(board_size)]
        self.current_player = 'X'

    def make_move(self, row, col):
        if self.board[row][col] == ' ':
            self.board[row][col] = self.current_player
            self.current_player = 'O' if self.current_player == 'X' else 'X'
            return True
        return False

    def check_winner(self):
        directions = [(0, 1), (1, 0), (1, 1), (1, -1)]
        for row in range(self.board_size):
            for col in range(self.board_size):
                cell = self.board[row][col]
                if cell != ' ':
                    for dx, dy in directions:
                        if self._check_five_in_a_row(row, col, dx, dy):
                            return cell
        return None

    def get_board(self):
        return [row[:] for row in self.board]

    def _check_five_in_a_row(self, row, col, dx, dy):
        count = 1
        symbol = self.board[row][col]
        for i in range(1, 5):
            r, c = row + dx * i, col + dy * i
            if not (0 <= r < self.board_size and 0 <= c < self.board_size):
                return False
            if self.board[r][c] != symbol:
                return False
            count += 1
        return count == 5