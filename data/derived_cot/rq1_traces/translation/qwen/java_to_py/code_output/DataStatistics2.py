import math

class DataStatistics2:
    def __init__(self, data_list):
        self.data = [float(x) for x in data_list]
    
    def getSum(self):
        return sum(self.data) if self.data else 0.0
    
    def getMin(self):
        return min(self.data) if self.data else float('nan')
    
    def getMax(self):
        return max(self.data) if self.data else float('nan')
    
    def getVariance(self):
        n = len(self.data)
        if n == 0:
            return float('nan')
        mean = self.getSum() / n
        squared_diffs = [(x - mean) ** 2 for x in self.data]
        return sum(squared_diffs) / n
    
    def getStdDeviation(self):
        variance = self.getVariance()
        if math.isnan(variance):
            return float('nan')
        return math.sqrt(variance)
    
    def getCorrelation(self):
        return 1.0