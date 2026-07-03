import math

class DataStatistics2:
    def __init__(self, data):
        self.data = data

    def get_sum(self):
        return sum(self.data)

    def get_min(self):
        return min(self.data)

    def get_max(self):
        return max(self.data)

    def get_variance(self):
        n = len(self.data)
        if n == 0:
            return float('nan')
        mean = self.get_sum() / n
        variance = 0.0
        for value in self.data:
            variance += (value - mean) ** 2
        variance /= n
        return round(variance * 100) / 100

    def get_std_deviation(self):
        variance = self.get_variance()
        std_dev = math.sqrt(variance)
        return round(std_dev * 100) / 100

    def get_correlation(self):
        n = len(self.data)
        if n < 2:
            return 1.0
        mean = self.get_sum() / n
        sum_sq = 0.0
        for value in self.data:
            sum_sq += (value - mean) ** 2
        return sum_sq / sum_sq