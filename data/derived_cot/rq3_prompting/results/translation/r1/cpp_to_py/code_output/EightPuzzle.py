import copy
from collections import deque

class EightPuzzle:
    GOAL_STATE = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    def __init__(self, initial_state=None):
        if initial_state is None:
            self.initial_state = []
        else:
            self.initial_state = initial_state

    def find_blank(self, state):
        for i in range(3):
            for j in range(3):
                if state[i][j] == 0:
                    return (i, j)
        return (-1, -1)

    def move(self, state, direction):
        i, j = self.find_blank(state)
        new_state = copy.deepcopy(state)   # same as copy by value
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
        open_list = deque()
        open_list.append((self.initial_state, []))
        closed_list = []

        while open_list:
            current_state, path = open_list.popleft()
            closed_list.append(current_state)

            if current_state == EightPuzzle.GOAL_STATE:
                return path

            for move_dir in self.get_possible_moves(current_state):
                new_state = self.move(current_state, move_dir)
                if new_state not in closed_list:
                    new_path = path + [move_dir]
                    open_list.append((new_state, new_path))

        return []

    # operator= is not needed in Python; assignment is just rebinding.
    # But to mimic the C++ interface, we can provide a method that creates a new instance:
    def assign(self, initial_state):
        return EightPuzzle(initial_state)