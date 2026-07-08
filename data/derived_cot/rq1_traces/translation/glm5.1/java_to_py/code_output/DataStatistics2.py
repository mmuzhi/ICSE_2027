import math
from typing import List

class DataStatistics2:
    def __init__(self, data: List[int]):
        # Convert List[int] to a list of floats, matching Java's mapToDouble
        self.data = [float(x) for x in data]

    def get_sum(self) -> float:
        # sum() of an empty list is 0.0, matching Java's DoubleStream.sum()
        return sum(self.data)

    def get_min(self) -> float:
        # Python's min() on empty list throws ValueError, Java returns NaN
        if not self.data:
            return float('nan')
        return min(self.data)

    def get_max(self) -> float:
        # Python's max() on empty list throws ValueError, Java returns NaN
        if not self.data:
            return float('nan')
        return max(self.data)

    def get_variance(self) -> float:
        # Python average of empty list throws, Java returns NaN
        if not self.data:
            return float('nan')
        
        mean = self.get_sum() / len(self.data)
        # Population variance (divided by N, not N-1), matching Java's .average()
        variance = sum((val - mean) ** 2 for val in self.data) / len(self.data)
        return variance

    def get_std_deviation(self) -> float:
        # math.sqrt(float('nan')) safely returns nan, matching Java's Math.sqrt(Double.NaN)
        return math.sqrt(self.get_variance())

    def get_correlation(self) -> float:
        return 1.0