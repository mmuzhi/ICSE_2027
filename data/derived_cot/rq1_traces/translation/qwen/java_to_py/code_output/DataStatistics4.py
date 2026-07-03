import math

def correlation_coefficient(data1, data2):
    n = len(data1)
    if n == 0:
        return 0
    if len(data2) != n:
        raise IndexError("List lengths do not match")
    
    mean1 = sum(data1) / n
    mean2 = sum(data2) / n
    
    numerator = sum((x - mean1) * (y - mean2) for x, y in zip(data1, data2))
    sum_sq1 = sum((x - mean1) ** 2 for x in data1)
    sum_sq2 = sum((y - mean2) ** 2 for y in data2)
    
    denominator = math.sqrt(sum_sq1) * math.sqrt(sum_sq2)
    
    return numerator / denominator if denominator != 0 else 0

def skewness(data):
    n = len(data)
    if n == 0:
        return 0
    
    mean = sum(data) / n
    sum_cubed_deviations = sum((x - mean) ** 3 for x in data)
    sum_squared_deviations = sum((x - mean) ** 2 for x in data)
    variance = sum_squared_deviations / n
    std_deviation = math.sqrt(variance)
    
    if std_deviation == 0:
        return 0
    
    denominator = (n - 1) * (n - 2) * (std_deviation ** 3)
    if denominator == 0:
        return 0
        
    return (sum_cubed_deviations * n) / denominator

def kurtosis(data):
    n = len(data)
    if n == 0:
        return float('nan')
    
    mean = sum(data) / n
    sum_squared_deviations = sum((x - mean) ** 2 for x in data)
    variance = sum_squared_deviations / n
    std_dev = math.sqrt(variance)
    
    if std_dev == 0:
        return float('nan')
    
    sum_fourth_powers = sum((x - mean) ** 4 for x in data)
    fourth_moment = sum_fourth_powers / n
    
    kurtosis_value = (fourth_moment / (std_dev ** 4)) - 3
    return kurtosis_value

def pdf(data, mu, sigma):
    if sigma == 0:
        return [float('nan')] * len(data)
    
    result = []
    for x in data:
        exponent = -0.5 * ((x - mu) / sigma) ** 2
        pdf_value = (1 / (sigma * math.sqrt(2 * math.pi))) * math.exp(exponent)
        result.append(pdf_value)
    
    return result