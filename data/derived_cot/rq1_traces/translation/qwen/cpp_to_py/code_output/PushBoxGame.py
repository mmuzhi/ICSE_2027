class PushBoxGame:
    def __init__(self, map_data=None):
        if map_data is None:
            map_data = []
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
        self._is_game_over = (box_on_target_count == self.target_count)
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
        else:
            return self.check_win()

        if new_player_row < 0 or new_player_row >= len(self.map) or \
           new_player_col < 0 or new_player_col >= len(self.map[0]):
            return self.check_win()

        if self.map[new_player_row][new_player_col] == '#':
            return self.check_win()

        if (new_player_row, new_player_col) in self.boxes:
            new_box_row = new_player_row + (new_player_row - self.player_row)
            new_box_col = new_player_col + (new_player_col - self.player_col)
            if new_box_row < 0 or new_box_row >= len(self.map) or \
               new_box_col < 0 or new_box_col >= len(self.map[0]) or \
               self.map[new_box_row][new_box_col] == '#':
                return self.check_win()

            box_index = self.boxes.index((new_player_row, new_player_col))
            self.boxes[box_index] = (new_box_row, new_box_col)

        self.player_row = new_player_row
        self.player_col = new_player_col

        return self.check_win()