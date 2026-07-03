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
    
    def get_variance(self):
        n = len(self.data)
        if n == 0:
            return float('nan')
        
        total = self.get_sum()
        mean = total / n
        variance = 0.0
        for value in self.data:
            diff = value - mean
            variance += diff ** 2
        variance /= n
        return round(variance * 100) / 100.0
    
    def get_std_deviation(self):
        variance = self.get_variance()
        std_dev = math.sqrt(variance)
        return round(std_dev * 100) / 100.0
    
    def get_correlation(self):
        n = len(self.data)
        if n < 2:
            return 1.0
        
        total = self.get_sum()
        mean = total / n
        sum_prod = 0.0
        sum_sq = 0.0
        for value in self.data:
            diff = value - mean
            term = diff * diff
            sum_prod += term
            sum_sq += term
        
        return sum_prod / sum_sq