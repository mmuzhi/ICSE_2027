import random

class Snake:

    class Position:

        def __init__(self, x, y):
            self._x = x
            self._y = y

        def getX(self):
            return self._x

        def getY(self):
            return self._y

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or self.__class__ != other.__class__:
                return False
            return self._x == other._x and self._y == other._y

        def __hash__(self):
            return 31 * self._x + self._y

    def __init__(self, SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, foodPosition):
        self.length = 1
        self.SCREEN_WIDTH = SCREEN_WIDTH
        self.SCREEN_HEIGHT = SCREEN_HEIGHT
        self.BLOCK_SIZE = BLOCK_SIZE
        self.positions = []
        self.positions.append(self.Position(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2))
        self.score = 0
        self.foodPosition = foodPosition
        self.random_gen = random.Random()

    def move(self, direction):
        cur = self.positions[0]
        x = direction.getX()
        y = direction.getY()
        new_x = (cur.getX() + x * self.BLOCK_SIZE) % self.SCREEN_WIDTH
        new_y = (cur.getY() + y * self.BLOCK_SIZE) % self.SCREEN_HEIGHT
        new_position = self.Position(new_x, new_y)
        if new_position == self.foodPosition:
            self.eat_food()
        if len(self.positions) > 2 and new_position in self.positions[2:]:
            self.reset()
        else:
            self.positions.insert(0, new_position)
            if len(self.positions) > self.length:
                self.positions.pop()

    def random_food_position(self):
        while True:
            x = self.random_gen.randint(0, self.SCREEN_WIDTH // self.BLOCK_SIZE - 1) * self.BLOCK_SIZE
            y = self.random_gen.randint(0, self.SCREEN_HEIGHT // self.BLOCK_SIZE - 1) * self.BLOCK_SIZE
            candidate = self.Position(x, y)
            if candidate not in self.positions:
                self.foodPosition = candidate
                break

    def reset(self):
        self.length = 1
        self.positions.clear()
        self.positions.append(self.Position(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2))
        self.score = 0
        self.random_food_position()

    def eat_food(self):
        self.length += 1
        self.score += 100
        self.random_food_position()

    def getLength(self):
        return self.length

    def getPositions(self):
        return self.positions

    def getScore(self):
        return self.score

    def getFoodPosition(self):
        return self.foodPosition