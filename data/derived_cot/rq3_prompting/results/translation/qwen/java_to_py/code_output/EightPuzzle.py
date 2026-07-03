import collections

class EightPuzzle:
    def __init__(self, initial_state):
        self.initial_state = tuple(tuple(row) for row in initial_state)
        self.goal_state = ((1, 2, 3), (4, 5, 6), (7, 8, 0))

    def find_blank(self, state):
        for i in range(3):
            for j in range(3):
                if state[i][j] == 0:
                    return (i, j)
        return None

    def move(self, state, direction):
        state_list = [list(row) for row in state]
        i, j = self.find_blank(state_list)
        new_state = [row[:] for row in state_list]

        if direction == "up" and i > 0:
            new_state[i][j] = new_state[i-1][j]
            new_state[i-1][j] = 0
        elif direction == "down" and i < 2:
            new_state[i][j] = new_state[i+1][j]
            new_state[i+1][j] = 0
        elif direction == "left" and j > 0:
            new_state[i][j] = new_state[i][j-1]
            new_state[i][j-1] = 0
        elif direction == "right" and j < 2:
            new_state[i][j] = new_state[i][j+1]
            new_state[i][j+1] = 0

        return tuple(tuple(row) for row in new_state)

    def get_possible_moves(self, state):
        i, j = self.find_blank(state)
        moves = []
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
        queue = collections.deque()
        queue.append((self.initial_state, []))
        visited = set()
        visited.add(self.initial_state)

        while queue:
            state, path = queue.popleft()
            if state == self.goal_state:
                return path

            for move in self.get_possible_moves(state):
                new_state = self.move(state, move)
                if new_state not in visited:
                    visited.add(new_state)
                    queue.append((new_state, path + [move]))
        return None