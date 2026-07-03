class PushBoxGame:
    def __init__(self, map=None):
        if map is None:
            self.map = []
        else:
            self.map = map[:]  # Make a shallow copy of the list
        self.player_row = 0
        self.player_col = 0
        self.targets = []      # List of tuples (row, col)
        self.boxes = []        # List of tuples (row, col)
        self.target_count = 0
        self._is_game_over = False
        self.init_game()
    
    def gat_map(self):
        return self.map[:]  # Return a copy of the map
    
    def is_game_over(self):
        return self._is_game_over
    
    def get_player_col(self):
        return self.player_col
    
    def get_player_row(self):
        return self.player_row
    
    def get_targets(self):
        return self.targets[:]  # Return a copy
    
    def get_boxes(self):
        return self.boxes[:]  # Return a copy
    
    def get_target_count(self):
        return self.target_count
    
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
    
    def check_win(self):
        box_on_target_count = 0
        for box in self.boxes:
            if box in self.targets:
                box_on_target_count += 1
        if box_on_target_count == self.target_count:
            self._is_game_over = True
        return self._is_game_over
    
    def move(self, direction):
        dr = 0
        dc = 0
        if direction == 'w':
            dr = -1
        elif direction == 's':
            dr = 1
        elif direction == 'a':
            dc = -1
        elif direction == 'd':
            dc = 1
        
        new_player_row = self.player_row + dr
        new_player_col = self.player_col + dc
        
        if not (0 <= new_player_row < len(self.map) and 0 <= new_player_col < len(self.map[0])):
            return self.check_win()
        
        if self.map[new_player_row][new_player_col] == '#':
            return self.check_win()
        
        new_pos = (new_player_row, new_player_col)
        if new_pos in self.boxes:
            new_box_row = new_player_row + dr
            new_box_col = new_player_col + dc
            if not (0 <= new_box_row < len(self.map) and 0 <= new_box_col < len(self.map[0])):
                return self.check_win()
            if self.map[new_box_row][new_box_col] == '#' or (new_box_row, new_box_col) in self.boxes:
                return self.check_win()
            
            self.boxes.remove(new_pos)
            self.boxes.append((new_box_row, new_box_col))
            self.player_row = new_player_row
            self.player_col = new_player_col
        else:
            self.player_row = new_player_row
            self.player_col = new_player_col
        
        return self.check_win()