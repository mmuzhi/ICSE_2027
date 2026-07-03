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
                if self.board[row][col] != ' ':
                    for dx, dy in directions:
                        if self._check_five_in_a_row(row, col, (dx, dy)):
                            return self.board[row][col]
        return None
    
    def getBoard(self):
        return [row[:] for row in self.board]
    
    def _check_five_in_a_row(self, row, col, direction):
        dx, dy = direction
        symbol = self.board[row][col]
        for step in range(1, 5):
            new_row = row + dx * step
            new_col = col + dy * step
            if not (0 <= new_row < self.board_size and 0 <= new_col < self.board_size):
                return False
            if self.board[new_row][new_col] != symbol:
                return False
        return True