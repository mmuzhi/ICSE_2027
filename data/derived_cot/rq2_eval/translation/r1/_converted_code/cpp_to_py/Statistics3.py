import math
from collections import defaultdict

def _variance(data, mean_value):
    total = 0.0
    for x in data:
        diff = x - mean_value
        total += diff * diff
    return total / (len(data) - 1)

class Statistics3:
    @staticmethod
    def mean(data):
        if len(data) == 0:
            return math.nan
        return float(sum(data)) / len(data)
    
    @staticmethod
    def median(data):
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 1:
            return sorted_data[n // 2]
        else:
            mid1 = sorted_data[n // 2 - 1]
            mid2 = sorted_data[n // 2]
            return (mid1 + mid2) / 2.0

    @staticmethod
    def mode(data):
        counts = {}
        for value in data:
            counts[value] = counts.get(value, 0) + 1
        
        max_count = 0
        for count in counts.values():
            if count > max_count:
                max_count = count
        
        mode_values = []
        for value, count in counts.items():
            if count == max_count:
                mode_values.append(value)
        
        return mode_values

    @staticmethod
    def correlation(x, y):
        if len(x) != len(y):
            raise ValueError("Vectors must be of the same length")
        n = len(x)
        if n == 0:
            return math.nan
        mean_x = Statistics3.mean(x)
        mean_y = Statistics3.mean(y)
        numerator = 0.0
        denom_x = 0.0
        denom_y = 0.0
        for i in range(n):
            diff_x = x[i] - mean_x
            diff_y = y[i] - mean_y
            numerator += diff_x * diff_y
            denom_x += diff_x * diff_x
            denom_y += diff_y * diff_y
        denominator = math.sqrt(denom_x * denom_y)
        if denominator == 0:
            return math.nan
        return numerator / denominator

    @staticmethod
    def correlation_matrix(data):
        if not data:
            return []
        num_rows = len(data)
        num_cols = len(data[0])
        for row in data:
            if len(row) != num_cols:
                raise ValueError("All rows must have the same number of columns")
        matrix = [[0.0] * num_cols for _ in range(num_cols)]
        for i in range(num_cols):
            for j in range(num_cols):
                col1 = [data[k][i] for k in range(num_rows)]
                col2 = [data[k][j] for k in range(num_rows)]
                matrix[i][j] = Statistics3.correlation(col1, col2)
        return matrix

    @staticmethod
    def standard_deviation(data):
        n = len(data)
        if n < 2:
            return math.nan
        mean_value = Statistics3.mean(data)
        var_value = _variance(data, mean_value)
        return math.sqrt(var_value)

    @staticmethod
    def z_score(data):
        mean_value = Statistics3.mean(data)
        std_deviation = Statistics3.standard_deviation(data)
        if std_deviation == 0:
            return [math.nan] * len(data)
        z_scores = []
        for x in data:
            z_scores.append((x - mean_value) / std_deviation)
        return z_scores