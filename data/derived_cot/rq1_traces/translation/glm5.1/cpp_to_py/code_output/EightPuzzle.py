from collections import deque

class EightPuzzle:
    goalState = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    def __init__(self, initial_state=None):
        if initial_state is None:
            self.initialState = []
        else:
            self.initialState = initial_state

    def find_blank(self, state):
        for i in range(3):
            for j in range(3):
                if state[i][j] == 0:
                    return (i, j)
        return (-1, -1)

    def move(self, state, direction):
        i, j = self.find_blank(state)
        # Deep copy the state
        new_state = [row[:] for row in state]

        if direction == "up" and i > 0:
            new_state[i][j], new_state[i - 1][j] = new_state[i - 1][j], new_state[i][j]
        elif direction == "down" and i < 2:
            new_state[i][j], new_state[i + 1][j] = new_state[i + 1][j], new_state[i][j]
        elif direction == "left" and j > 0:
            new_state[i][j], new_state[i][j - 1] = new_state[i][j - 1], new_state[i][j]
        elif direction == "right" and j < 2:
            new_state[i][j], new_state[i][j + 1] = new_state[i][j + 1], new_state[i][j]

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
        # Using a set of tuples for O(1) lookups, as Python lists are unhashable 
        # and checking membership on a list of lists is extremely slow.
        closed_list = set()

        open_list.append((self.initialState, []))

        while open_list:
            current_state, path = open_list.popleft()
            
            # Convert to tuple of tuples for hashability in the set
            current_state_tuple = tuple(tuple(row) for row in current_state)
            closed_list.add(current_state_tuple)

            if current_state == self.goalState:
                return path

            for move_dir in self.get_possible_moves(current_state):
                new_state = self.move(current_state, move_dir)
                new_state_tuple = tuple(tuple(row) for row in new_state)
                
                if new_state_tuple not in closed_list:
                    new_path = path + [move_dir]
                    open_list.append((new_state, new_path))

        return []

    def assign(self, initial_state):
        """
        Equivalent to the C++ operator=.
        Note: Python does not allow overriding the assignment operator `=`.
        The original C++ code returns a new EightPuzzle instance rather than 
        modifying the current one, so this method replicates that exact behavior.
        """
        return EightPuzzle(initial_state)