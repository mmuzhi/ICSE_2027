import math

class DataStatistics2:

    def __init__(self, data):
        self.data = [float(x) for x in data]

    def get_sum(self):
        return sum(self.data)

    def get_min(self):
        if len(self.data) == 0:
            return float('nan')
        return min(self.data)

    def get_max(self):
        if len(self.data) == 0:
            return float('nan')
        return max(self.data)

    def get_variance(self):
        n = len(self.data)
        if n == 0:
            return float('nan')
        mean = self.get_sum() / n
        squared_diffs = [(x - mean) ** 2 for x in self.data]
        return sum(squared_diffs) / n

    def get_std_deviation(self):
        variance = self.get_variance()
        return math.sqrt(variance)

    def get_correlation(self):
        return 1.0