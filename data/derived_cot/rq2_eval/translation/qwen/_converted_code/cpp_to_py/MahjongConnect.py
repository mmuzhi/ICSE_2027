import random

class MahjongConnect:
    def __init__(self, board_size, icons):
        self.BOARD_SIZE = board_size
        self.ICONS = icons
        self.board = self.create_board()

    def create_board(self):
        rows, cols = self.BOARD_SIZE
        new_board = [[' ' for _ in range(cols)] for _ in range(rows)]
        for i in range(rows):
            for j in range(cols):
                new_board[i][j] = random.choice(self.ICONS)
        return new_board

    def is_valid_move(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2
        rows, cols = self.BOARD_SIZE
        
        # Check if positions are within bounds
        if not (0 <= x1 < rows and 0 <= y1 < cols and 0 <= x2 < rows and 0 <= y2 < cols):
            return False
        
        # Positions cannot be the same
        if pos1 == pos2:
            return False
        
        # Icons must match
        if self.board[x1][y1] != self.board[x2][y2]:
            return False
        
        # Check for a valid path
        return self.has_path(pos1, pos2)

    def has_path(self, pos1, pos2):
        stack = [pos1]
        visited = set()
        
        while stack:
            current = stack.pop()
            if current == pos2:
                return True
            
            if current in visited:
                continue
            visited.add(current)
            
            x, y = current
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nx, ny = x + dx, y + dy
                if (0 <= nx < self.BOARD_SIZE[0] and 
                    0 <= ny < self.BOARD_SIZE[1] and 
                    (nx, ny) not in visited and 
                    self.board[nx][ny] == self.board[x][y]):
                    stack.append((nx, ny))
                    
        return False

    def remove_icons(self, pos1, pos2):
        x1, y1 = pos1
        x2, y2 = pos2
        self.board[x1][y1] = ' '
        self.board[x2][y2] = ' '

    def is_game_over(self):
        for row in self.board:
            for cell in row:
                if cell != ' ':
                    return False
        return True