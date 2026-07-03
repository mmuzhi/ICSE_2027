import random
from typing import List

class Snake:
    class Position:
        def __init__(self, x: int, y: int) -> None:
            self.x = x
            self.y = y
        
        def __eq__(self, other: object) -> bool:
            if not isinstance(other, Snake.Position):
                return False
            return self.x == other.x and self.y == other.y
        
        def __hash__(self) -> int:
            return hash((self.x, self.y))
    
    def __init__(self, SCREEN_WIDTH: int, SCREEN_HEIGHT: int, BLOCK_SIZE: int, food_position: Position) -> None:
        self.length = 1
        self.SCREEN_WIDTH = SCREEN_WIDTH
        self.SCREEN_HEIGHT = SCREEN_HEIGHT
        self.BLOCK_SIZE = BLOCK_SIZE
        self.positions: List[Snake.Position] = [Snake.Position(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)]
        self.score = 0
        self.food_position = food_position
        self.random = random.Random()
    
    def move(self, direction: Position) -> None:
        current_head = self.positions[0]
        dx = direction.x
        dy = direction.y
        
        new_x = (current_head.x + dx * self.BLOCK_SIZE) % self.SCREEN_WIDTH
        new_y = (current_head.y + dy * self.BLOCK_SIZE) % self.SCREEN_HEIGHT
        new_head = Snake.Position(new_x, new_y)
        
        if new_head == self.food_position:
            self.eat_food()
        else:
            if len(self.positions) > 2 and new_head in self.positions[2:]:
                self.reset()
            else:
                self.positions.insert(0, new_head)
                if len(self.positions) > self.length:
                    self.positions.pop()
    
    def random_food_position(self) -> None:
        while True:
            x = self.random.randint(0, self.SCREEN_WIDTH // self.BLOCK_SIZE) * self.BLOCK_SIZE
            y = self.random.randint(0, self.SCREEN_HEIGHT // self.BLOCK_SIZE) * self.BLOCK_SIZE
            new_food = Snake.Position(x, y)
            if new_food not in self.positions:
                self.food_position = new_food
                break
    
    def reset(self) -> None:
        self.length = 1
        self.positions = [Snake.Position(self.SCREEN_WIDTH // 2, self.SCREEN_HEIGHT // 2)]
        self.score = 0
        self.random_food_position()
    
    def eat_food(self) -> None:
        self.length += 1
        self.score += 100
        self.random_food_position()
    
    def get_length(self) -> int:
        return self.length
    
    def get_positions(self) -> List[Position]:
        return self.positions
    
    def get_score(self) -> int:
        return self.score
    
    def get_food_position(self) -> Position:
        return self.food_position