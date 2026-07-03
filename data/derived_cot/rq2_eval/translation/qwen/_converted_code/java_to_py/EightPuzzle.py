import collections
import copy

class EightPuzzle:

    def __init__(self, initialState):
        self.initial_state = [row[:] for row in initialState]
        self.goal_state = ((1, 2, 3), (4, 5, 6), (7, 8, 0))

    def find_blank(self, state):
        for i in range(3):
            for j in range(3):
                if state[i][j] == 0:
                    return (i, j)
        return None

    def move(self, state, direction):
        i, j = self.find_blank(state)
        new_state = [row[:] for row in state]
        if direction == 'up' and i > 0:
            new_state[i][j], new_state[i - 1][j] = (new_state[i - 1][j], new_state[i][j])
        elif direction == 'down' and i < 2:
            new_state[i][j], new_state[i + 1][j] = (new_state[i + 1][j], new_state[i][j])
        elif direction == 'left' and j > 0:
            new_state[i][j], new_state[i][j - 1] = (new_state[i][j - 1], new_state[i][j])
        elif direction == 'right' and j < 2:
            new_state[i][j], new_state[i][j + 1] = (new_state[i][j + 1], new_state[i][j])
        return new_state

    def get_possible_moves(self, state):
        i, j = self.find_blank(state)
        moves = []
        if i > 0:
            moves.append('up')
        if i < 2:
            moves.append('down')
        if j > 0:
            moves.append('left')
        if j < 2:
            moves.append('right')
        return moves

    def stateToString(self, state):
        return ''.join((str(num) for row in state for num in row))

    def solve(self):
        start = tuple((tuple(row) for row in self.initial_state))
        goal = tuple((tuple(row) for row in self.goal_state))
        if start == goal:
            return []
        open_list = collections.deque()
        closed_set = set()
        open_list.append((start, []))
        while open_list:
            state, path = open_list.popleft()
            state_str = self.stateToString(state)
            if state_str in closed_set:
                continue
            closed_set.add(state_str)
            if state == goal:
                return path
            for move in self.get_possible_moves(state):
                new_state = self.move(state, move)
                new_state_tuple = tuple((tuple(row) for row in new_state))
                if self.stateToString(new_state_tuple) not in closed_set:
                    open_list.append((new_state_tuple, path + [move]))
        return None

class Node:
    pass