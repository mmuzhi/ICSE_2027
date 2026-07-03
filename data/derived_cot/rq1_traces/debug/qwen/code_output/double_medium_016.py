import random

class Solution:

    def __init__(self, radius: float, x_center: float, y_center: float):
        self.radius = radius
        self.x_center = x_center
        self.y_center = y_center
        self.r = radius

    def randPoint(self) -> List[float]:
        angle = random.uniform(0, 2 * math.pi)
        r = math.sqrt(random.uniform(0, self.r ** 2))
        x = self.x_center + r * math.cos(angle)
        y = self.y_center + r * math.sin(angle)
        return [x, y]