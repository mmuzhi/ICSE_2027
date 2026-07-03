import math

class Statistics3:
    @staticmethod
    def mean(data):
        if not data:
            return float('nan')
        return sum(data) / len(data)

    @staticmethod
    def _variance(data, mean_val):
        # sample variance (n-1 denominator)
        if len(data) < 2:
            return 0.0  # not called in normal flow
        var_sum = sum((x - mean_val) ** 2 for x in data)
        return var_sum / (len(data) - 1)

    @staticmethod
    def median(data):
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 1:
            return sorted_data[n // 2]
        else:
            return (sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2.0

    @staticmethod
    def mode(data):
        counts = {}
        for val in data:
            counts[val] = counts.get(val, 0) + 1
        if not counts:
            return []
        max_count = max(counts.values())
        mode_vals = [k for k in sorted(counts) if counts[k] == max_count]
        return mode_vals

    @staticmethod
    def correlation(x, y):
        n = len(x)
        if n != len(y):
            raise ValueError("Vectors must be of the same length")
        if n == 0:
            return float('nan')
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
            return float('nan')
        return numerator / denominator

    @staticmethod
    def correlation_matrix(data):
        if not data:
            return []
        num_rows = len(data)
        num_cols = len(data[0])
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
            return float('nan')
        mean_val = Statistics3.mean(data)
        var = Statistics3._variance(data, mean_val)
        return math.sqrt(var)

    @staticmethod
    def z_score(data):
        mean_val = Statistics3.mean(data)
        std_dev = Statistics3.standard_deviation(data)
        # Replicate C++ behaviour: only check for zero (NaN comparison always false)
        if std_dev == 0:
            return [float('nan')] * len(data)
        z_scores = [(x - mean_val) / std_dev for x in data]
        return z_scores