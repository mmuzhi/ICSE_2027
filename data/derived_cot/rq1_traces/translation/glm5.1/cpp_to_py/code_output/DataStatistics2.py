import math

class DataStatistics2:
    def __init__(self, data):
        self.data = list(data)

    def _cpp_round(self, x):
        """Mimics C++ std::round which rounds half away from zero."""
        if math.isnan(x) or math.isinf(x):
            return x
        return math.floor(x + 0.5) if x >= 0 else math.ceil(x - 0.5)

    def get_sum(self):
        return sum(self.data)

    def get_min(self):
        return min(self.data)

    def get_max(self):
        return max(self.data)

    def get_variance(self):
        # C++ returns NaN for 0.0 / 0.0 when size is 0, Python raises ZeroDivisionError
        if len(self.data) == 0:
            return float('nan')
        
        mean = self.get_sum() / len(self.data)
        variance = 0.0
        for value in self.data:
            variance += math.pow(value - mean, 2)
        variance /= len(self.data)
        return self._cpp_round(variance * 100) / 100

    def get_std_deviation(self):
        variance = self.get_variance()
        # C++ std::sqrt of negative returns NaN, Python raises ValueError
        if variance < 0:
            std_dev = float('nan')
        else:
            std_dev = math.sqrt(variance)
        return self._cpp_round(std_dev * 100) / 100

    def get_correlation(self):
        if len(self.data) < 2:
            return 1.0
        
        mean = self.get_sum() / len(self.data)
        sum_prod = 0.0
        sum_sq = 0.0
        for value in self.data:
            diff_sq = math.pow(value - mean, 2)
            sum_prod += diff_sq
            sum_sq += diff_sq
        
        # C++ 0.0 / 0.0 returns NaN, Python raises ZeroDivisionError
        if sum_sq == 0.0:
            return float('nan')
        return sum_prod / sum_sq