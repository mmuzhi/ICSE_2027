import copy
from collections import deque

class EightPuzzle:
    def __init__(self, initialState):
        self.initialState = self.deep_copy(initialState)
        self.goalState = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    def find_blank(self, state):
        for i in range(3):
            for j in range(3):
                if state[i][j] == 0:
                    return [i, j]
        return None

    def move(self, state, direction):
        blank = self.find_blank(state)
        i, j = blank[0], blank[1]
        newState = self.deep_copy(state)

        if direction == "up":
            if i > 0:
                newState[i][j] = newState[i-1][j]
                newState[i-1][j] = 0
        elif direction == "down":
            if i < 2:
                newState[i][j] = newState[i+1][j]
                newState[i+1][j] = 0
        elif direction == "left":
            if j > 0:
                newState[i][j] = newState[i][j-1]
                newState[i][j-1] = 0
        elif direction == "right":
            if j < 2:
                newState[i][j] = newState[i][j+1]
                newState[i][j+1] = 0
        return newState

    def get_possible_moves(self, state):
        moves = []
        blank = self.find_blank(state)
        i, j = blank[0], blank[1]

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
        openList = deque()
        closedList = set()
        initialNode = (self.initialState, [])
        openList.append(initialNode)

        while openList:
            currentState, path = openList.popleft()
            closedList.add(self.state_to_string(currentState))

            if currentState == self.goalState:
                return path

            for move in self.get_possible_moves(currentState):
                newState = self.move(currentState, move)
                newStateStr = self.state_to_string(newState)
                if newStateStr not in closedList:
                    newPath = path + [move]
                    openList.append((newState, newPath))
        return None

    def state_to_string(self, state):
        s = ""
        for row in state:
            for val in row:
                s += str(val)
        return s

    def deep_copy(self, original):
        return copy.deepcopy(original)