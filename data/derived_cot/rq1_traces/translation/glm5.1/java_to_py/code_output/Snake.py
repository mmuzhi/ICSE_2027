import math
import random
from typing import List


class Snake:
    class Position:
        def __init__(self, x: int, y: int):
            self._x = x
            self._y = y

        def getX(self) -> int:
            return self._x

        def getY(self) -> int:
            return self._y

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(self) is not type(other):
                return False
            return self._x == other._x and self._y == other._y

        def __hash__(self):
            return 31 * self._x + self._y

    def __init__(self, SCREEN_WIDTH: int, SCREEN_HEIGHT: int, BLOCK_SIZE: int, foodPosition: 'Snake.Position'):
        self.length = 1
        self.SCREEN_WIDTH = SCREEN_WIDTH
        self.SCREEN_HEIGHT = SCREEN_HEIGHT
        self.BLOCK_SIZE = BLOCK_SIZE
        self.positions: List[Snake.Position] = [Snake.Position(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)]
        self.score = 0
        self.foodPosition = foodPosition
        self.random = random.Random()

    def move(self, direction: 'Snake.Position'):
        cur = self.positions[0]
        x = direction.getX()
        y = direction.getY()

        new_x = int(math.fmod(cur.getX() + (x * self.BLOCK_SIZE), self.SCREEN_WIDTH))
        new_y = int(math.fmod(cur.getY() + (y * self.BLOCK_SIZE), self.SCREEN_HEIGHT))

        new_position = Snake.Position(new_x, new_y)

        if new_position == self.foodPosition:
            self.eatFood()

        if len(self.positions) > 2 and new_position in self.positions[2:]:
            self.reset()
        else:
            self.positions.insert(0, new_position)
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

    def getLength(self) -> int:
        return self.length

    def getPositions(self) -> List['Snake.Position']:
        return self.positions

    def getScore(self) -> int:
        return self.score

    def getFoodPosition(self) -> 'Snake.Position':
        return self.foodPosition