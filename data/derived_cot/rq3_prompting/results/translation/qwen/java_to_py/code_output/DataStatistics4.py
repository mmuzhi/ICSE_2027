import math
from typing import List

def correlation_coefficient(data1: List[float], data2: List[float]) -> float:
    n = len(data1)
    if n == 0:
        return 0.0
        
    mean1 = sum(data1) / n
    mean2 = sum(data2) / n
    
    numerator = sum((x - mean1) * (y - mean2) for x, y in zip(data1, data2))
    
    variance1 = sum((x - mean1) ** 2 for x in data1) / n
    variance2 = sum((y - mean2) ** 2 for y in data2) / n
    
    denominator = math.sqrt(variance1) * math.sqrt(variance2)
    
    return numerator / denominator if denominator != 0 else 0.0

def skewness(data: List[float]) -> float:
    n = len(data)
    if n < 3:
        return 0.0
        
    mean = sum(data) / n
    variance = sum((x - mean) ** 2 for x in data) / n
    std_deviation = math.sqrt(variance)
    
    if std_deviation == 0:
        return 0.0
        
    centered_cubed_sum = sum((x - mean) ** 3 for x in data)
    return (n * centered_cubed_sum) / ((n - 1) * (n - 2) * (std_deviation ** 3))

def kurtosis(data: List[float]) -> float:
    n = len(data)
    if n < 4:
        return float('nan')
        
    mean = sum(data) / n
    variance = sum((x - mean) ** 2 for x in data) / n
    std_dev = math.sqrt(variance)
    
    if std_dev == 0:
        return float('nan')
        
    fourth_moment = sum((x - mean) ** 4 for x in data) / n
    return (fourth_moment / (std_dev ** 4)) - 3

def pdf(data: List[float], mu: float, sigma: float) -> List[float]:
    if sigma <= 0:
        raise ValueError("Sigma must be positive")
    return [
        (1 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((x - mu) / sigma) ** 2)
        for x in data
    ]