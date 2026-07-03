import math
from typing import List

class DataStatistics2:
    def __init__(self, data: List[int]) -> None:
        self.data = [float(x) for x in data]

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
        mean = self.getSum() / len(self.data)
        return sum((x - mean) ** 2 for x in self.data) / len(self.data)

    def getStdDeviation(self) -> float:
        return math.sqrt(self.getVariance())

    def getCorrelation(self) -> float:
        return 1.0