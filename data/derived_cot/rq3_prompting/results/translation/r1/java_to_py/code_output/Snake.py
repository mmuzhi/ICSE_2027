import random
import math


class Snake:
    class Position:
        def __init__(self, x: int, y: int):
            self._x = x
            self._y = y

        def get_x(self) -> int:
            return self._x

        def get_y(self) -> int:
            return self._y

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(other) != type(self):
                return False
            return self._x == other._x and self._y == other._y

        def __hash__(self):
            return 31 * self._x + self._y

    def __init__(self, SCREEN_WIDTH: int, SCREEN_HEIGHT: int, BLOCK_SIZE: int, food_position: Position):
        self._length = 1
        self.SCREEN_WIDTH = SCREEN_WIDTH
        self.SCREEN_HEIGHT = SCREEN_HEIGHT
        self.BLOCK_SIZE = BLOCK_SIZE
        self._positions = [self.Position(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)]
        self._score = 0
        self._food_position = food_position
        self._random = random.Random()

    def _java_mod(self, a: int, b: int) -> int:
        # replicates Java's truncation‑toward‑zero modulo for positive divisor
        return int(math.fmod(a, b))

    def move(self, direction: Position):
        cur = self._positions[0]
        x = direction.get_x()
        y = direction.get_y()
        new_x = self._java_mod(cur.get_x() + x * self.BLOCK_SIZE, self.SCREEN_WIDTH)
        new_y = self._java_mod(cur.get_y() + y * self.BLOCK_SIZE, self.SCREEN_HEIGHT)
        new_position = self.Position(new_x, new_y)

        if new_position == self._food_position:
            self.eat_food()

        if len(self._positions) > 2 and new_position in self._positions[2:]:
            self.reset()
        else:
            self._positions.insert(0, new_position)
            if len(self._positions) > self._length:
                self._positions.pop()

    def random_food_position(self):
        while True:
            x = self._random.randrange(0, self.SCREEN_WIDTH // self.BLOCK_SIZE) * self.BLOCK_SIZE
            y = self._random.randrange(0, self.SCREEN_HEIGHT // self.BLOCK_SIZE) * self.BLOCK_SIZE
            food = self.Position(x, y)
            if food not in self._positions:
                self._food_position = food
                break

    def reset(self):
        self._length = 1
        self._positions.clear()
        self._positions.append(self.Position(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2))
        self._score = 0
        self.random_food_position()

    def eat_food(self):
        self._length += 1
        self._score += 100
        self.random_food_position()

    def get_length(self) -> int:
        return self._length

    def get_positions(self):
        return self._positions

    def get_score(self) -> int:
        return self._score

    def get_food_position(self):
        return self._food_position