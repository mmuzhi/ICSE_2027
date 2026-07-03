import math

class DataStatistics2:

    def __init__(self, data_list):
        self.data = [float(x) for x in data_list]

    def get_sum(self):
        return sum(self.data) if self.data else 0.0

    def get_min(self):
        return min(self.data) if self.data else float('nan')

    def get_max(self):
        return max(self.data) if self.data else float('nan')

    def get_variance(self):
        n = len(self.data)
        if n == 0:
            return float('nan')
        mean = self.get_sum() / n
        squared_diffs = [(x - mean) ** 2 for x in self.data]
        return sum(squared_diffs) / n

    def get_std_deviation(self):
        variance = self.get_variance()
        if math.isnan(variance):
            return float('nan')
        return math.sqrt(variance)

    def get_correlation(self):
        return 1.0