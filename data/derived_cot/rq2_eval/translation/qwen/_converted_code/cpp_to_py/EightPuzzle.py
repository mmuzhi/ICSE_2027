from collections import deque

class EightPuzzle:
    def __init__(self, initial_state=None):
        self.initial_state = initial_state if initial_state is not None else []
        self.goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
    
    def find_blank(self, state):
        for i, row in enumerate(state):
            for j, value in enumerate(row):
                if value == 0:
                    return (i, j)
        return (-1, -1)
    
    def move(self, state, direction):
        i, j = self.find_blank(state)
        new_state = [row[:] for row in state]
        
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
        if self.initial_state == self.goal_state:
            return []
        
        open_list = deque()
        open_list.append((self.initial_state, []))
        
        while open_list:
            state, path = open_list.popleft()
            i, j = self.find_blank(state)
            
            if state == self.goal_state:
                return path
            
            for move in self.get_possible_moves(state):
                new_state = self.move(state, move)
                open_list.append((new_state, path + [move]))
        
        return []