import math


class DataStatistics2:
    def __init__(self, data):
        self.data = list(data)

    def get_sum(self):
        return sum(self.data)

    def get_min(self):
        return min(self.data)

    def get_max(self):
        return max(self.data)

    def _round(self, x):
        if x >= 0:
            return math.floor(x + 0.5)
        else:
            return math.ceil(x - 0.5)

    def get_variance(self):
        mean = self.get_sum() / len(self.data)
        variance = 0.0
        for value in self.data:
            variance += (value - mean) ** 2
        variance /= len(self.data)
        return self._round(variance * 100) / 100

    def get_std_deviation(self):
        variance = self.get_variance()
        std_dev = math.sqrt(variance)
        return self._round(std_dev * 100) / 100

    def get_correlation(self):
        if len(self.data) < 2:
            return 1.0
        mean = self.get_sum() / len(self.data)
        sum_prod = 0.0
        sum_sq = 0.0
        for value in self.data:
            sum_prod += (value - mean) * (value - mean)
            sum_sq += (value - mean) * (value - mean)
        if sum_sq == 0.0:
            return float('nan')
        return sum_prod / sum_sq