class PushBoxGame:

    def __init__(self, map):
        self.map = [row[:] for row in map]
        self.playerRow = 0
        self.playerCol = 0
        self.targets = []
        self.boxes = []
        self.targetCount = 0
        self.isGameOver = False
        self.init_game()

    def init_game(self):
        for row in range(len(self.map)):
            for col in range(len(self.map[row])):
                if self.map[row][col] == 'O':
                    self.playerRow = row
                    self.playerCol = col
                elif self.map[row][col] == 'G':
                    self.targets.append((row, col))
                    self.targetCount += 1
                elif self.map[row][col] == 'X':
                    self.boxes.append((row, col))

    def check_win(self):
        boxOnTargetCount = 0
        for box in self.boxes:
            if box in self.targets:
                boxOnTargetCount += 1
        self.isGameOver = boxOnTargetCount == self.targetCount
        return self.isGameOver

    def move(self, direction):
        newPlayerRow = self.playerRow
        newPlayerCol = self.playerCol
        if direction == 'w':
            newPlayerRow -= 1
        elif direction == 's':
            newPlayerRow += 1
        elif direction == 'a':
            newPlayerCol -= 1
        elif direction == 'd':
            newPlayerCol += 1
        if self.isValidMove(newPlayerRow, newPlayerCol):
            if self.isBoxAt(newPlayerRow, newPlayerCol):
                boxPosition = self.getBoxPosition(newPlayerRow, newPlayerCol)
                dr = newPlayerRow - self.playerRow
                dc = newPlayerCol - self.playerCol
                newBoxRow = newPlayerRow + dr
                newBoxCol = newPlayerCol + dc
                if self.isValidMove(newBoxRow, newBoxCol) and (not self.isBoxAt(newBoxRow, newBoxCol)):
                    self.moveBox(boxPosition, newBoxRow, newBoxCol)
                    self.playerRow = newPlayerRow
                    self.playerCol = newPlayerCol
            else:
                self.playerRow = newPlayerRow
                self.playerCol = newPlayerCol
        return self.check_win()

    def isValidMove(self, row, col):
        return 0 <= row < len(self.map) and 0 <= col < len(self.map[row]) and (self.map[row][col] != '#')

    def isBoxAt(self, row, col):
        return (row, col) in self.boxes

    def getBoxPosition(self, row, col):
        for box in self.boxes:
            if box == (row, col):
                return box
        return None

    def moveBox(self, boxPosition, newRow, newCol):
        if boxPosition in self.boxes:
            index = self.boxes.index(boxPosition)
            self.boxes[index] = (newRow, newCol)

    def getPlayerCol(self):
        return self.playerCol

    def getPlayerRow(self):
        return self.playerRow

    def getTargets(self):
        return list(self.targets)

    def getTargetCount(self):
        return self.targetCount

    def getMap(self):
        return [row[:] for row in self.map]

    def getBoxes(self):
        return list(self.boxes)

    def isGameOver(self):
        return self.isGameOver