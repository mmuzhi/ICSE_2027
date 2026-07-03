import math
from collections import Counter

class Statistics3:

    def median(self, data):
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 1:
            return sorted_data[n // 2]
        else:
            return (sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2.0

    def mode(self, data):
        if not data:
            return []
        counts = Counter(data)
        max_count = max(counts.values())
        modes = [k for k, v in counts.items() if v == max_count]
        modes.sort()
        return modes

    def correlation(self, x, y):
        if len(x) != len(y) or len(x) == 0:
            return None
        meanX = sum(x) / len(x)
        meanY = sum(y) / len(y)
        numerator = 0.0
        denomX = 0.0
        denomY = 0.0
        for i in range(len(x)):
            diffX = x[i] - meanX
            diffY = y[i] - meanY
            numerator += diffX * diffY
            denomX += diffX * diffX
            denomY += diffY * diffY
        if denomX == 0 or denomY == 0:
            return None
        return numerator / math.sqrt(denomX * denomY)

    def mean(self, data):
        if len(data) == 0:
            return None
        return sum(data) / len(data)

    def correlation_matrix(self, data):
        numCols = len(data[0])
        matrix = [[0.0] * numCols for _ in range(numCols)]
        for i in range(numCols):
            col1 = [row[i] for row in data]
            for j in range(numCols):
                col2 = [row[j] for row in data]
                corr_val = self.correlation(col1, col2)
                if corr_val is None:
                    matrix[i][j] = float('nan')
                else:
                    matrix[i][j] = corr_val
        return matrix

    def standard_deviation(self, data):
        if len(data) < 2:
            return None
        mu = self.mean(data)
        variance = sum(((x - mu) ** 2 for x in data)) / (len(data) - 1)
        return math.sqrt(variance)

    def z_score(self, data):
        mu = self.mean(data)
        std = self.standard_deviation(data)
        if mu is None or std is None or std == 0:
            return None
        return [(x - mu) / std for x in data]