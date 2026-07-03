import math
from typing import List, Dict, Any

class Statistics3:
    @staticmethod
    def mean(data: List[int]) -> float:
        if not data:
            return float('nan')
        return sum(data) / len(data)
    
    @staticmethod
    def variance(data: List[int], mean_value: float) -> float:
        n = len(data)
        if n == 0:
            return float('nan')
        variance_sum = 0.0
        for x in data:
            diff = x - mean_value
            variance_sum += diff * diff
        return variance_sum / (n - 1) if n > 1 else float('nan')
    
    @staticmethod
    def median(data: List[int]) -> float:
        n = len(data)
        if n == 0:
            raise IndexError("Cannot compute median of empty data")
        sorted_data = sorted(data)
        if n % 2 == 1:
            return sorted_data[n//2]
        else:
            return (sorted_data[n//2 - 1] + sorted_data[n//2]) / 2.0
    
    @staticmethod
    def mode(data: List[int]) -> List[int]:
        counts: Dict[int, int] = {}
        for value in data:
            counts[value] = counts.get(value, 0) + 1
        if not counts:
            return []
        max_count = max(counts.values())
        mode_values = [value for value, count in counts.items() if count == max_count]
        return mode_values
    
    @staticmethod
    def correlation(x: List[int], y: List[int]) -> float:
        n = len(x)
        if n != len(y):
            raise ValueError("Vectors must be of the same length")
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
        if denominator == 0:
            return float('nan')
        return numerator / denominator
    
    @staticmethod
    def correlation_matrix(data: List[List[int]]) -> List[List[float]]:
        num_rows = len(data)
        if num_rows == 0:
            return []
        num_cols = len(data[0])
        matrix = [[0.0] * num_cols for _ in range(num_cols)]
        for i in range(num_cols):
            col1 = [data[k][i] for k in range(num_rows)]
            for j in range(num_cols):
                col2 = [data[k][j] for k in range(num_rows)]
                matrix[i][j] = Statistics3.correlation(col1, col2)
        return matrix
    
    @staticmethod
    def standard_deviation(data: List[int]) -> float:
        n = len(data)
        if n < 2:
            return float('nan')
        mean_value = Statistics3.mean(data)
        var = Statistics3.variance(data, mean_value)
        return math.sqrt(var)
    
    @staticmethod
    def z_score(data: List[int]) -> List[float]:
        mean_value = Statistics3.mean(data)
        std_deviation = Statistics3.standard_deviation(data)
        if std_deviation == float('nan') or std_deviation == 0.0:
            return [float('nan')] * len(data)
        z_scores = [(x - mean_value) / std_deviation for x in data]
        return z_scores