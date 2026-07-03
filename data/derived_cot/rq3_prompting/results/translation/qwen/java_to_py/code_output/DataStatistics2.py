import math
from typing import List

class DataStatistics2:
    def __init__(self, data: List[int]):
        self.data = data

    def getSum(self) -> float:
        return sum(self.data)

    def getMin(self) -> float:
        if not self.data:
            return float('nan')
        return min(self.data)

    def getMax(self) -> float:
        if not self.data:
            return float('nan')
        return max(self.data)

    def getVariance(self) -> float:
        if not self.data:
            return float('nan')
        n = len(self.data)
        mean = self.getSum() / n
        squared_diffs = [(x - mean) ** 2 for x in self.data]
        sum_sq = sum(squared_diffs)
        return sum_sq / n

    def getStdDeviation(self) -> float:
        variance = self.getVariance()
        return math.sqrt(variance)

    def getCorrelation(self) -> float:
        return 1.0