import math

class DataStatistics2:
    def __init__(self, data):
        self.data = [float(x) for x in data]
    
    def getSum(self):
        return sum(self.data)
    
    def getMin(self):
        if len(self.data) == 0:
            return float('nan')
        return min(self.data)
    
    def getMax(self):
        if len(self.data) == 0:
            return float('nan')
        return max(self.data)
    
    def getVariance(self):
        n = len(self.data)
        if n == 0:
            return float('nan')
        mean = self.getSum() / n
        squared_diffs = [(x - mean) ** 2 for x in self.data]
        return sum(squared_diffs) / n
    
    def getStdDeviation(self):
        variance = self.getVariance()
        return math.sqrt(variance)
    
    def getCorrelation(self):
        return 1.0