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
            return 0.0
        mean = self.get_sum() / n
        variance = 0.0
        for value in self.data:
            variance += (value - mean) ** 2
        variance /= n
        variance_rounded = self.round_two_decimals(variance)
        return variance_rounded

    def get_std_deviation(self):
        variance = self.get_variance()
        std_dev = math.sqrt(variance)
        std_dev_rounded = self.round_two_decimals(std_dev)
        return std_dev_rounded

    def get_correlation(self):
        n = len(self.data)
        if n < 2:
            return 1.0
        mean = self.get_sum() / n
        sum_sq = 0.0
        for value in self.data:
            sum_sq += (value - mean) ** 2
        return 1.0  # Since correlation of a vector with itself is 1.0

    @staticmethod
    def round_two_decimals(x):
        temp = x * 100
        if temp >= 0:
            return math.floor(temp + 0.5) / 100
        else:
            return math.ceil(temp - 0.5) / 100