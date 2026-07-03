import random
import time

def cpp_mod(a, b):
    res = a % b
    if res != 0 and a < 0:
        res -= b
    return res

class Snake:
    def __init__(self, screenWidth, screenHeight, blockSize, foodPosition):
        self.length = 1
        self.SCREEN_WIDTH = screenWidth
        self.SCREEN_HEIGHT = screenHeight
        self.BLOCK_SIZE = blockSize
        self.score = 0
        self.food_position = foodPosition
        self.positions = [(screenWidth // 2, screenHeight // 2)]
    
    def move(self, direction):
        cur = self.positions[0]
        x, y = direction

        new_x = cpp_mod(cur[0] + x * self.BLOCK_SIZE, self.SCREEN_WIDTH)
        new_y = cpp_mod(cur[1] + y * self.BLOCK_SIZE, self.SCREEN_HEIGHT)
        new_head = (new_x, new_y)

        if new_head == self.food_position:
            self.eat_food()
        
        if len(self.positions) > 2 and new_head in self.positions[2:]:
            self.reset()
        else:
            self.positions.insert(0, new_head)
            if len(self.positions) > self.length:
                self.positions.pop()
    
    def random_food_position(self):
        random.seed(int(time.time()))
        while True:
            x = random.randint(0, self.SCREEN_WIDTH // self.BLOCK_SIZE - 1) * self.BLOCK_SIZE
            y = random.randint(0, self.SCREEN_HEIGHT // self.BLOCK_SIZE - 1) * self.BLOCK_SIZE
            candidate = (x, y)
            if candidate not in self.positions:
                self.food_position = candidate
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
        return self.positions[:]
    
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