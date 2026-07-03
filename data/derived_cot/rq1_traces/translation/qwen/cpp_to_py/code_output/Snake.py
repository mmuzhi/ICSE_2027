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
        head_x, head_y = self.positions[0]
        dx, dy = direction
        new_x = (head_x + dx * self.BLOCK_SIZE) % self.SCREEN_WIDTH
        new_y = (head_y + dy * self.BLOCK_SIZE) % self.SCREEN_HEIGHT
        new_pos = (new_x, new_y)
        
        if new_pos == self.food_position:
            self.eat_food()
        else:
            self.positions.insert(0, new_pos)
            if len(self.positions) > self.length:
                self.positions.pop()

    def random_food_position(self):
        random.seed(int(time.time()))
        valid_position = False
        while not valid_position:
            x = random.randint(0, (self.SCREEN_WIDTH // self.BLOCK_SIZE) - 1) * self.BLOCK_SIZE
            y = random.randint(0, (self.SCREEN_HEIGHT // self.BLOCK_SIZE) - 1) * self.BLOCK_SIZE
            new_food_pos = (x, y)
            if new_food_pos not in self.positions:
                self.food_position = new_food_pos
                valid_position = True

    def reset(self):
        self.length = 1
        self.positions = [(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2)]
        self.score = 0
        self.random_food_position()

    def eat_food(self):
        self.length += 1
        self.score += 100
        self.random_food_position()