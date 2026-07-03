import math
from typing import List


class DataStatistics2:
    def __init__(self, data: List[int]):
        self.data = [float(x) for x in data]

    def get_sum(self) -> float:
        return sum(self.data)

    def get_min(self) -> float:
        return min(self.data) if self.data else math.nan

    def get_max(self) -> float:
        return max(self.data) if self.data else math.nan

    def get_variance(self) -> float:
        if not self.data:
            return math.nan
        mean = self.get_sum() / len(self.data)
        return sum((val - mean) ** 2 for val in self.data) / len(self.data)

    def get_std_deviation(self) -> float:
        return math.sqrt(self.get_variance())

    def get_correlation(self) -> float:
        return 1.0