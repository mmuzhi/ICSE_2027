import math

class DataStatistics4:

    @staticmethod
    def correlationCoefficient(data1, data2):
        n = len(data1)
        mean1 = sum(data1) / len(data1) if data1 else 0.0
        mean2 = sum(data2) / len(data2) if data2 else 0.0

        numerator = sum((data1[i] - mean1) * (data2[i] - mean2) for i in range(n))

        sum1 = sum((x - mean1) ** 2 for x in data1)
        sum2 = sum((y - mean2) ** 2 for y in data2)
        denominator = math.sqrt(sum1) * math.sqrt(sum2)

        return 0.0 if denominator == 0 else numerator / denominator

    @staticmethod
    def skewness(data):
        n = len(data)
        mean = sum(data) / n if n else 0.0
        variance = sum((x - mean) ** 2 for x in data) / n if n else 0.0
        std_deviation = math.sqrt(variance)

        if std_deviation == 0:
            return 0.0

        numerator = sum((x - mean) ** 3 for x in data) * n
        denominator = (n - 1) * (n - 2) * (std_deviation ** 3)

        if denominator == 0:
            if numerator == 0:
                return float('nan')
            return float('inf') if numerator > 0 else float('-inf')

        return numerator / denominator

    @staticmethod
    def kurtosis(data):
        n = len(data)
        mean = sum(data) / n if n else 0.0
        variance = sum((x - mean) ** 2 for x in data) / n if n else 0.0
        std_dev = math.sqrt(variance)

        if std_dev == 0:
            return float('nan')

        centered_data = [x - mean for x in data]
        fourth_moment = sum(x ** 4 for x in centered_data) / n if n else 0.0

        return (fourth_moment / (std_dev ** 4)) - 3

    @staticmethod
    def pdf(data, mu, sigma):
        return [(1 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((x - mu) / sigma) ** 2) for x in data]