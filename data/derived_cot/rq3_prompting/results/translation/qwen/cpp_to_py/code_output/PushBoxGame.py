class PushBoxGame:
    def __init__(self, map_data=None):
        if map_data is None:
            self.map = []
            self.player_row = 0
            self.player_col = 0
            self.targets = []
            self.boxes = []
            self.target_count = 0
            self._is_game_over = False
            self.init_game()
        else:
            self.map = map_data
            self.player_row = 0
            self.player_col = 0
            self.targets = []
            self.boxes = []
            self.target_count = 0
            self._is_game_over = False
            self.init_game()

    def init_game(self):
        for row_idx, row in enumerate(self.map):
            for col_idx, cell in enumerate(row):
                if cell == 'O':
                    self.player_row = row_idx
                    self.player_col = col_idx
                elif cell == 'G':
                    self.targets.append((row_idx, col_idx))
                    self.target_count += 1
                elif cell == 'X':
                    self.boxes.append((row_idx, col_idx))

    def gat_map(self):
        return self.map

    def is_game_over(self):
        return self._is_game_over

    def get_player_col(self):
        return self.player_col

    def get_player_row(self):
        return self.player_row

    def get_targets(self):
        return self.targets

    def get_boxes(self):
        return self.boxes

    def get_target_count(self):
        return self.target_count

    def check_win(self):
        box_on_target_count = 0
        for box in self.boxes:
            if box in self.targets:
                box_on_target_count += 1
        if box_on_target_count == self.target_count:
            self._is_game_over = True
        return self._is_game_over

    def move(self, direction):
        new_player_row = self.player_row
        new_player_col = self.player_col

        if direction == 'w':
            new_player_row -= 1
        elif direction == 's':
            new_player_row += 1
        elif direction == 'a':
            new_player_col -= 1
        elif direction == 'd':
            new_player_col += 1

        if self.map[new_player_row][new_player_col] == '#':
            return False

        if (new_player_row, new_player_col) in self.boxes:
            dx = new_player_row - self.player_row
            dy = new_player_col - self.player_col
            new_box_row = new_player_row + dx
            new_box_col = new_player_col + dy

            if self.map[new_box_row][new_box_col] == '#':
                return False

            box_to_move = (new_player_row, new_player_col)
            self.boxes.remove(box_to_move)
            self.boxes.append((new_box_row, new_box_col))

        self.player_row = new_player_row
        self.player_col = new_player_col

        self.check_win()
        return self._is_game_over