from typing import List, Tuple, Optional


class PushBoxGame:
    def __init__(self, map: List[List[str]]):
        self.map = [row[:] for row in map]  # deep copy
        self.player_row: int = 0
        self.player_col: int = 0
        self.targets: List[List[int]] = []
        self.boxes: List[List[int]] = []
        self.target_count: int = 0
        self.is_game_over: bool = False
        self._init_game()

    def _init_game(self) -> None:
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

    def check_win(self) -> bool:
        box_on_target_count = 0
        for box in self.boxes:
            for target in self.targets:
                if box == target:
                    box_on_target_count += 1
        self.is_game_over = (box_on_target_count == self.target_count)
        return self.is_game_over

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

        if self._is_valid_move(new_player_row, new_player_col):
            if self._is_box_at(new_player_row, new_player_col):
                box_pos = self._get_box_position(new_player_row, new_player_col)
                new_box_row = new_player_row + (new_player_row - self.player_row)
                new_box_col = new_player_col + (new_player_col - self.player_col)

                if self._is_valid_move(new_box_row, new_box_col) and not self._is_box_at(new_box_row, new_box_col):
                    self._move_box(box_pos, new_box_row, new_box_col)
                    self.player_row = new_player_row
                    self.player_col = new_player_col
            else:
                self.player_row = new_player_row
                self.player_col = new_player_col

        return self.check_win()

    def _is_valid_move(self, row: int, col: int) -> bool:
        return (0 <= row < len(self.map) and
                0 <= col < len(self.map[row]) and
                self.map[row][col] != '#')

    def _is_box_at(self, row: int, col: int) -> bool:
        return any(box == [row, col] for box in self.boxes)

    def _get_box_position(self, row: int, col: int) -> Optional[List[int]]:
        for box in self.boxes:
            if box == [row, col]:
                return box
        return None

    def _move_box(self, box_position: List[int], new_row: int, new_col: int) -> None:
        for i, box in enumerate(self.boxes):
            if box == box_position:
                self.boxes[i] = [new_row, new_col]
                break

    def is_game_over(self) -> bool:
        return self.is_game_over

    def get_player_col(self) -> int:
        return self.player_col

    def get_player_row(self) -> int:
        return self.player_row

    def get_targets(self) -> List[List[int]]:
        return list(self.targets)

    def get_target_count(self) -> int:
        return self.target_count

    def get_map(self) -> List[List[str]]:
        return self.map

    def get_boxes(self) -> List[List[int]]:
        return list(self.boxes)