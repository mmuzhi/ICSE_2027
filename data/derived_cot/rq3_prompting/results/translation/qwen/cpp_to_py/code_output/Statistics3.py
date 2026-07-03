import math
import numpy as np
from collections import defaultdict

class Statistics3:
    @staticmethod
    def mean(data):
        if not data:
            return float('nan')
        return sum(data) / len(data)

    @staticmethod
    def variance(data, mean_value):
        variance_sum = 0.0
        for x in data:
            diff = x - mean_value
            variance_sum += diff * diff
        return variance_sum / (len(data) - 1) if len(data) > 1 else float('nan')

    @staticmethod
    def median(data):
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 1:
            return sorted_data[n//2]
        else:
            return (sorted_data[n//2 - 1] + sorted_data[n//2]) / 2.0

    @staticmethod
    def mode(data):
        counts = defaultdict(int)
        for value in data:
            counts[value] += 1
        
        if not counts:
            return []
        
        max_count = max(counts.values())
        mode_values = [k for k, v in counts.items() if v == max_count]
        return mode_values

    @staticmethod
    def correlation(x, y):
        n = len(x)
        if n != len(y) or n == 0:
            raise ValueError("Vectors must be of the same length and non-empty")
        
        mean_x = Statistics3.mean(x)
        mean_y = Statistics3.mean(y)
        
        numerator = 0.0
        denominator_x = 0.0
        denominator_y = 0.0
        
        for i in range(n):
            diff_x = x[i] - mean_x
            diff_y = y[i] - mean_y
            numerator += diff_x * diff_y
            denominator_x += diff_x * diff_x
            denominator_y += diff_y * diff_y
        
        denominator = math.sqrt(denominator_x * denominator_y)
        return numerator / denominator if denominator != 0 else float('nan')

    @staticmethod
    def correlation_matrix(data):
        if not data or not data[0]:
            return np.array([])
        
        num_rows = len(data)
        num_cols = len(data[0])
        
        corr_matrix = np.zeros((num_cols, num_cols))
        
        for i in range(num_cols):
            for j in range(num_cols):
                col1 = [row[i] for row in data]
                col2 = [row[j] for row in data]
                corr_matrix[i][j] = Statistics3.correlation(col1, col2)
        
        return corr_matrix.tolist()

    @staticmethod
    def standard_deviation(data):
        n = len(data)
        if n < 2:
            return float('nan')
        mean_val = Statistics3.mean(data)
        var = Statistics3.variance(data, mean_val)
        return math.sqrt(var)

    @staticmethod
    def z_score(data):
        mean_val = Statistics3.mean(data)
        std_dev = Statistics3.standard_deviation(data)
        
        if std_dev in (0, float('nan')):
            return [float('nan')] * len(data)
        
        return [(x - mean_val) / std_dev for x in data]