import math

def correlation_coefficient(data1, data2):
    n = len(data1)
    if n == 0:
        return 0.0
    mean1 = sum(data1) / n
    mean2 = sum(data2) / n

    numerator = sum((data1[i] - mean1) * (data2[i] - mean2) for i in range(n))
    denom1 = math.sqrt(sum((x - mean1) ** 2 for x in data1))
    denom2 = math.sqrt(sum((x - mean2) ** 2 for x in data2))
    denominator = denom1 * denom2

    return numerator / denominator if denominator != 0 else 0.0

def skewness(data):
    n = len(data)
    if n == 0:
        return 0.0
    mean = sum(data) / n
    variance = sum((x - mean) ** 2 for x in data) / n
    std_dev = math.sqrt(variance)

    if std_dev == 0:
        return 0.0

    skew = (sum((x - mean) ** 3 for x in data) * n /
            ((n - 1) * (n - 2) * (std_dev ** 3)))
    return skew

def kurtosis(data):
    n = len(data)
    if n == 0:
        return float('nan')
    mean = sum(data) / n
    variance = sum((x - mean) ** 2 for x in data) / n
    std_dev = math.sqrt(variance)

    if std_dev == 0:
        return float('nan')

    centered = [x - mean for x in data]
    fourth_moment = sum(x ** 4 for x in centered) / n
    kurt = fourth_moment / (std_dev ** 4) - 3
    return kurt

def pdf(data, mu, sigma):
    factor = 1.0 / (sigma * math.sqrt(2 * math.pi))
    return [factor * math.exp(-0.5 * ((x - mu) / sigma) ** 2) for x in data]