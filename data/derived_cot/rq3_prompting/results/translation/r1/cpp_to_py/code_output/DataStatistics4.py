import math

class DataStatistics4:
    @staticmethod
    def correlation_coefficient(data1, data2):
        n = len(data1)
        mean1 = sum(data1) / n
        mean2 = sum(data2) / n

        numerator = 0.0
        denom1 = 0.0
        denom2 = 0.0
        for i in range(n):
            d1 = data1[i] - mean1
            d2 = data2[i] - mean2
            numerator += d1 * d2
            denom1 += d1 * d1
            denom2 += d2 * d2

        denominator = math.sqrt(denom1) * math.sqrt(denom2)
        return numerator / denominator if denominator != 0 else 0.0

    @staticmethod
    def skewness(data):
        n = len(data)
        mean = sum(data) / n

        variance = sum((x - mean) ** 2 for x in data) / n
        std_dev = math.sqrt(variance)

        if std_dev == 0:
            return 0.0

        skew = sum((x - mean) ** 3 for x in data)
        skew *= n / ((n - 1) * (n - 2) * (std_dev ** 3))
        return skew

    @staticmethod
    def kurtosis(data):
        n = len(data)
        mean = sum(data) / n

        variance = sum((x - mean) ** 2 for x in data) / n
        std_dev = math.sqrt(variance)

        if std_dev == 0:
            return float('nan')

        fourth_moment = sum((x - mean) ** 4 for x in data) / n
        return (fourth_moment / (std_dev ** 4)) - 3.0

    @staticmethod
    def pdf(data, mu, sigma):
        result = []
        for x in data:
            value = (1.0 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((x - mu) / sigma) ** 2)
            result.append(value)
        return result