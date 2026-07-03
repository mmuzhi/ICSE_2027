import math
import random as random_module


class Snake:
    class Position:
        __slots__ = ('x', 'y')

        def __init__(self, x, y):
            self.x = x
            self.y = y

        def getX(self):
            return self.x

        def getY(self):
            return self.y

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(self) is not type(other):
                return False
            return self.x == other.x and self.y == other.y

        def __hash__(self):
            return 31 * self.x + self.y

    def __init__(self, SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, foodPosition):
        self.length = 1
        self.SCREEN_WIDTH = SCREEN_WIDTH
        self.SCREEN_HEIGHT = SCREEN_HEIGHT
        self.BLOCK_SIZE = BLOCK_SIZE
        self.positions = [Snake.Position(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)]
        self.score = 0
        self.foodPosition = foodPosition
        self.random = random_module.Random()

    def move(self, direction):
        cur = self.positions[0]
        x = direction.getX()
        y = direction.getY()

        newX = int(math.fmod(cur.getX() + (x * self.BLOCK_SIZE), self.SCREEN_WIDTH))
        newY = int(math.fmod(cur.getY() + (y * self.BLOCK_SIZE), self.SCREEN_HEIGHT))

        newPosition = Snake.Position(newX, newY)

        if newPosition == self.foodPosition:
            self.eatFood()

        if len(self.positions) > 2 and newPosition in self.positions[2:]:
            self.reset()
        else:
            self.positions.insert(0, newPosition)
            if len(self.positions) > self.length:
                self.positions.pop()

    def randomFoodPosition(self):
        while True:
            x = self.random.randint(0, self.SCREEN_WIDTH // self.BLOCK_SIZE - 1) * self.BLOCK_SIZE
            y = self.random.randint(0, self.SCREEN_HEIGHT // self.BLOCK_SIZE - 1) * self.BLOCK_SIZE
            self.foodPosition = Snake.Position(x, y)
            if self.foodPosition not in self.positions:
                break

    def reset(self):
        self.length = 1
        self.positions.clear()
        self.positions.append(Snake.Position(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2))
        self.score = 0
        self.randomFoodPosition()

    def eatFood(self):
        self.length += 1
        self.score += 100
        self.randomFoodPosition()

    def getLength(self):
        return self.length

    def getPositions(self):
        return self.positions

    def getScore(self):
        return self.score

    def getFoodPosition(self):
        return self.foodPosition