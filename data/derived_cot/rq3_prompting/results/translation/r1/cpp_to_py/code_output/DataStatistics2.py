import math

class DataStatistics2:
    def __init__(self, data):
        self.data = list(data)  # make a mutable copy, preserve behavior of storing vector

    def get_sum(self):
        return sum(self.data)

    def get_min(self):
        return min(self.data)

    def get_max(self):
        return max(self.data)

    def get_variance(self):
        n = len(self.data)
        mean = self.get_sum() / n
        variance = sum((x - mean) ** 2 for x in self.data) / n
        return round(variance * 100) / 100.0

    def get_std_deviation(self):
        variance = self.get_variance()
        std_dev = math.sqrt(variance)
        return round(std_dev * 100) / 100.0

    def get_correlation(self):
        if len(self.data) < 2:
            return 1.0
        mean = self.get_sum() / len(self.data)
        sum_prod = 0.0
        sum_sq = 0.0
        for x in self.data:
            diff = x - mean
            sum_prod += diff * diff
            sum_sq += diff * diff
        # sum_prod and sum_sq are always equal -> correlation is always 1.0
        return sum_prod / sum_sq