from typing import List, Tuple

class PushBoxGame:
    def __init__(self, map: List[str] = None):
        if map is None:
            map = []
        self.map = map
        self.player_row = 0
        self.player_col = 0
        self.targets: List[Tuple[int, int]] = []
        self.boxes: List[Tuple[int, int]] = []
        self.target_count = 0
        self._is_game_over = False
        self.init_game()

    def gat_map(self) -> List[str]:
        return self.map

    def is_game_over(self) -> bool:
        return self._is_game_over

    def get_player_col(self) -> int:
        return self.player_col

    def get_player_row(self) -> int:
        return self.player_row

    def get_targets(self) -> List[Tuple[int, int]]:
        return self.targets

    def get_boxes(self) -> List[Tuple[int, int]]:
        return self.boxes

    def get_target_count(self) -> int:
        return self.target_count

    def init_game(self):
        for row, line in enumerate(self.map):
            for col, ch in enumerate(line):
                if ch == 'O':
                    self.player_row = row
                    self.player_col = col
                elif ch == 'G':
                    self.targets.append((row, col))
                    self.target_count += 1
                elif ch == 'X':
                    self.boxes.append((row, col))

    def check_win(self) -> bool:
        box_on_target_count = sum(1 for box in self.boxes if box in self.targets)
        if box_on_target_count == self.target_count:
            self._is_game_over = True
        return self._is_game_over

    def move(self, direction: str) -> bool:
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

        # No bounds check – replicates C++ behavior
        if self.map[new_player_row][new_player_col] != '#':
            new_pos = (new_player_row, new_player_col)
            if new_pos in self.boxes:
                # Box is pushed
                new_box_row = new_player_row + (new_player_row - self.player_row)
                new_box_col = new_player_col + (new_player_col - self.player_col)
                # Check if new box position is wall (again no bounds check)
                if self.map[new_box_row][new_box_col] != '#':
                    # Remove the box at its old position
                    box_idx = self.boxes.index(new_pos)
                    self.boxes.pop(box_idx)
                    # Add the box at new position
                    self.boxes.append((new_box_row, new_box_col))
                    # Move player
                    self.player_row = new_player_row
                    self.player_col = new_player_col
            else:
                # Just move player
                self.player_row = new_player_row
                self.player_col = new_player_col

        return self.check_win()