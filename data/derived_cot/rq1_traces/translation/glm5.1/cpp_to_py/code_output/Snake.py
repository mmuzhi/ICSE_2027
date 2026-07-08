import random
import time

class Snake:
    def __init__(self, screen_width, screen_height, block_size, food_position):
        self.length = 1
        self.SCREEN_WIDTH = screen_width
        self.SCREEN_HEIGHT = screen_height
        self.BLOCK_SIZE = block_size
        self.score = 0
        self.food_position = food_position
        self.positions = [(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2)]

    @staticmethod
    def _c_mod(a, b):
        """
        Mimics C++ modulo behavior.
        In C++, the result of modulo has the sign of the dividend, which can yield 
        negative coordinates for screen wrapping. Python's modulo always yields a 
        non-negative result. This preserves the exact C++ behavior.
        """
        res = a % b
        return res if a >= 0 or res == 0 else res - b

    def move(self, direction):
        cur = self.positions[0]
        x, y = direction

        new_pos = (
            self._c_mod(cur[0] + x * self.BLOCK_SIZE, self.SCREEN_WIDTH),
            self._c_mod(cur[1] + y * self.BLOCK_SIZE, self.SCREEN_HEIGHT)
        )

        if new_pos == self.food_position:
            self.eat_food()

        if len(self.positions) > 2 and new_pos in self.positions[2:]:
            self.reset()
        else:
            self.positions.insert(0, new_pos)
            if len(self.positions) > self.length:
                self.positions.pop()

    def random_food_position(self):
        # Mimics the C++ side effect of resetting the random seed on every call
        random.seed(int(time.time()))
        while True:
            self.food_position = (
                random.randrange(self.SCREEN_WIDTH // self.BLOCK_SIZE) * self.BLOCK_SIZE,
                random.randrange(self.SCREEN_HEIGHT // self.BLOCK_SIZE) * self.BLOCK_SIZE
            )
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

    def get_length(self):
        return self.length

    def get_positions(self):
        # Return a copy to match C++ return-by-value semantics
        return self.positions.copy()

    def get_score(self):
        return self.score

    def get_food_position(self):
        return self.food_position

    def get_SCREEN_WIDTH(self):
        return self.SCREEN_WIDTH

    def get_SCREEN_HEIGHT(self):
        return self.SCREEN_HEIGHT

    def get_BLOCK_SIZE(self):
        return self.BLOCK_SIZE