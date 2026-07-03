import random
import time

class Snake:
    def __init__(self, screenWidth, screenHeight, blockSize, foodPosition):
        self.length = 1
        self.SCREEN_WIDTH = screenWidth
        self.SCREEN_HEIGHT = screenHeight
        self.BLOCK_SIZE = blockSize
        self.positions = [(screenWidth // 2, screenHeight // 2)]
        self.score = 0
        self.food_position = foodPosition

    def move(self, direction):
        cur = self.positions[0]
        x, y = direction
        new_pos = ((cur[0] + x * self.BLOCK_SIZE) % self.SCREEN_WIDTH,
                   (cur[1] + y * self.BLOCK_SIZE) % self.SCREEN_HEIGHT)
        
        if new_pos == self.food_position:
            self.eat_food()
        else:
            if len(self.positions) > 2 and new_pos in self.positions[2:]:
                self.reset()
            else:
                self.positions.insert(0, new_pos)
                if len(self.positions) > self.length:
                    self.positions.pop()

    def random_food_position(self):
        random.seed(int(time.time()))
        valid_position = False
        while not valid_position:
            x = (random.randint(0, (self.SCREEN_WIDTH // self.BLOCK_SIZE) - 1) * self.BLOCK_SIZE
            y = (random.randint(0, (self.SCREEN_HEIGHT // self.BLOCK_SIZE) - 1) * self.BLOCK_SIZE
            self.food_position = (x, y)
            valid_position = True
            for pos in self.positions:
                if pos == self.food_position:
                    valid_position = False
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