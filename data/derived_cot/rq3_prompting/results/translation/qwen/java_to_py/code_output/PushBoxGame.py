class PushBoxGame:
    def __init__(self, map_data):
        # Initialize the game state
        self.map = [row[:] for row in map_data]  # Deep copy the map
        self.player_row = 0
        self.player_col = 0
        self.targets = []
        self.boxes = []
        self.target_count = 0
        self.is_game_over = False
        self.init_game()

    def init_game(self):
        # Initialize player, targets, and boxes positions
        for row_idx, row in enumerate(self.map):
            for col_idx, cell in enumerate(row):
                if cell == 'O':
                    self.player_row = row_idx
                    self.player_col = col_idx
                elif cell == 'G':
                    self.targets.append([row_idx, col_idx])
                    self.target_count += 1
                elif cell == 'X':
                    self.boxes.append([row_idx, col_idx])

    def check_win(self):
        # Count boxes on targets
        box_on_target_count = 0
        for box in self.boxes:
            for target in self.targets:
                if box == target:
                    box_on_target_count += 1
        self.is_game_over = (box_on_target_count == self.target_count)
        return self.is_game_over

    def move(self, direction):
        # Calculate new player position
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

        # Check if the move is valid
        if self.is_valid_move(new_player_row, new_player_col):
            if self.is_box_at(new_player_row, new_player_col):
                # Move the box if possible
                box_pos = self.get_box_position(new_player_row, new_player_col)
                new_box_row = new_player_row + (new_player_row - self.player_row)
                new_box_col = new_player_col + (new_player_col - self.player_col)
                if self.is_valid_move(new_box_row, new_box_col) and not self.is_box_at(new_box_row, new_box_col):
                    self.move_box(box_pos, new_box_row, new_box_col)
                    self.player_row = new_player_row
                    self.player_col = new_player_col
            else:
                # Move the player
                self.player_row = new_player_row
                self.player_col = new_player_col
        return self.check_win()

    def is_valid_move(self, row, col):
        # Check if the position is within bounds and not a wall
        return (0 <= row < len(self.map) and 
                0 <= col < len(self.map[row]) and 
                self.map[row][col] != '#')

    def is_box_at(self, row, col):
        # Check if there's a box at the given position
        for box in self.boxes:
            if box == [row, col]:
                return True
        return False

    def get_box_position(self, row, col):
        # Get the box position if exists
        for box in self.boxes:
            if box == [row, col]:
                return box
        return None

    def move_box(self, box_pos, new_row, new_col):
        # Move the box to the new position
        for i, box in enumerate(self.boxes):
            if box == box_pos:
                self.boxes[i] = [new_row, new_col]
                break

    def is_game_over(self):
        return self.is_game_over

    def get_player_col(self):
        return self.player_col

    def get_player_row(self):
        return self.player_row

    def get_targets(self):
        return [target[:] for target in self.targets]  # Return a copy

    def get_box_count(self):
        return self.target_count  # Assuming target_count is the box count

    def get_map(self):
        return [row[:] for row in self.map]  # Return a copy of the map

    def get_boxes(self):
        return [box[:] for box in self.boxes]  # Return a copy of the boxes