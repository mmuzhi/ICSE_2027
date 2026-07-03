import math
import statistics

def correlation_coefficient(data1, data2):
    n = len(data1)
    mean1 = statistics.mean(data1) if n > 0 else 0.0
    mean2 = statistics.mean(data2) if n > 0 else 0.0
    
    numerator = sum((data1[i] - mean1) * (data2[i] - mean2) for i in range(n))
    
    sum_sq_dev1 = sum((x - mean1) ** 2 for x in data1)
    sum_sq_dev2 = sum((x - mean2) ** 2 for x in data2)
    denominator = math.sqrt(sum_sq_dev1) * math.sqrt(sum_sq_dev2)
    
    if denominator == 0:
        return 0.0
    return numerator / denominator

def skewness(data):
    n = len(data)
    if n == 0:
        return 0.0
    mean = statistics.mean(data)
    variance = statistics.variance(data) if n > 1 else 0.0
    std_deviation = math.sqrt(variance)
    
    if std_deviation == 0:
        return 0.0
    
    sum_cubed_dev = sum((x - mean) ** 3 for x in data)
    skewness_value = sum_cubed_dev * n / ((n - 1) * (n - 2) * std_deviation ** 3)
    return skewness_value

def kurtosis(data):
    n = len(data)
    if n == 0:
        return float('nan')
    mean = statistics.mean(data)
    if n == 1:
        variance = 0.0
    else:
        variance = statistics.variance(data)
    std_dev = math.sqrt(variance) if variance != 0 else 0.0
    
    if std_dev == 0:
        return float('nan')
    
    centered_data = [x - mean for x in data]
    fourth_moment = sum(x ** 4 for x in centered_data) / n
    kurtosis_value = fourth_moment / (std_dev ** 4) - 3
    return kurtosis_value

def pdf(data, mu, sigma):
    if sigma == 0:
        return [float('nan')] * len(data)
    factor = 1 / (sigma * math.sqrt(2 * math.pi))
    return [factor * math.exp(-0.5 * ((x - mu) / sigma) ** 2) for x in data]