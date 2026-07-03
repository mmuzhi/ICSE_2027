from collections import deque

class EightPuzzle:
    def __init__(self, initial_state=None):
        if initial_state is None:
            self.initialState = []
        else:
            self.initialState = initial_state
        self.goalState = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    def find_blank(self, state):
        for i in range(3):
            for j in range(3):
                if state[i][j] == 0:
                    return (i, j)
        return (-1, -1)

    def move(self, state, direction):
        i, j = self.find_blank(state)
        new_state = [list(row) for row in state]
        if direction == "up" and i > 0:
            new_state[i][j], new_state[i-1][j] = new_state[i-1][j], new_state[i][j]
        elif direction == "down" and i < 2:
            new_state[i][j], new_state[i+1][j] = new_state[i+1][j], new_state[i][j]
        elif direction == "left" and j > 0:
            new_state[i][j], new_state[i][j-1] = new_state[i][j-1], new_state[i][j]
        elif direction == "right" and j < 2:
            new_state[i][j], new_state[i][j+1] = new_state[i][j+1], new_state[i][j]
        return new_state

    def get_possible_moves(self, state):
        moves = []
        i, j = self.find_blank(state)
        if i > 0:
            moves.append("up")
        if i < 2:
            moves.append("down")
        if j > 0:
            moves.append("left")
        if j < 2:
            moves.append("right")
        return moves

    def solve(self):
        if not self.initialState:
            return []
        open_list = deque()
        open_list.append((self.initialState, []))
        closed_list = []
        while open_list:
            current_state, path = open_list.popleft()
            closed_list.append(current_state)
            if current_state == self.goalState:
                return path
            for move_direction in self.get_possible_moves(current_state):
                new_state = self.move(current_state, move_direction)
                if new_state not in closed_list:
                    new_path = path + [move_direction]
                    open_list.append((new_state, new_path))
        return []