import random
import time

class Snake:
    def __init__(self, screen_width: int, screen_height: int, block_size: int, food_position: tuple):
        self.length = 1
        self.SCREEN_WIDTH = screen_width
        self.SCREEN_HEIGHT = screen_height
        self.BLOCK_SIZE = block_size
        self.score = 0
        self.food_position = food_position
        self.positions = [(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2)]

    def _c_mod(self, a: int, b: int) -> int:
        """Simulate C++ integer modulo (truncates toward zero)."""
        return a - int(a / b) * b

    def move(self, direction: tuple):
        cur = self.positions[0]
        x, y = direction
        new_x = self._c_mod(cur[0] + x * self.BLOCK_SIZE, self.SCREEN_WIDTH)
        new_y = self._c_mod(cur[1] + y * self.BLOCK_SIZE, self.SCREEN_HEIGHT)
        new_pos = (new_x, new_y)

        if new_pos == self.food_position:
            self.eat_food()

        if len(self.positions) > 2 and new_pos in self.positions[2:]:
            self.reset()
        else:
            self.positions.insert(0, new_pos)
            if len(self.positions) > self.length:
                self.positions.pop()

    def random_food_position(self):
        random.seed(int(time.time()))
        while True:
            fx = random.randrange(0, self.SCREEN_WIDTH // self.BLOCK_SIZE) * self.BLOCK_SIZE
            fy = random.randrange(0, self.SCREEN_HEIGHT // self.BLOCK_SIZE) * self.BLOCK_SIZE
            self.food_position = (fx, fy)
            if self.food_position not in self.positions:
                break

    def reset(self):
        self.length = 1
        self.positions = [(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2)]
        self.score = 0
        self.random_food_position()

    def eat_food(self):
        self.length += 1
        self.score += 100
        self.random_food_position()

    def get_length(self) -> int:
        return self.length

    def get_positions(self) -> list:
        return self.positions

    def get_score(self) -> int:
        return self.score

    def get_food_position(self) -> tuple:
        return self.food_position

    def get_SCREEN_WIDTH(self) -> int:
        return self.SCREEN_WIDTH

    def get_SCREEN_HEIGHT(self) -> int:
        return self.SCREEN_HEIGHT

    def get_BLOCK_SIZE(self) -> int:
        return self.BLOCK_SIZE