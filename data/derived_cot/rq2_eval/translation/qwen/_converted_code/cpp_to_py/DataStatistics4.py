import math
import numpy as np

class DataStatistics4:
    @staticmethod
    def correlation_coefficient(data1, data2):
        n = len(data1)
        if n == 0:
            return 0.0
        mean1 = sum(data1) / n
        mean2 = sum(data2) / n
        
        numerator = 0.0
        denominator1 = 0.0
        denominator2 = 0.0
        
        for i in range(n):
            diff1 = data1[i] - mean1
            diff2 = data2[i] - mean2
            numerator += diff1 * diff2
            denominator1 += diff1 * diff1
            denominator2 += diff2 * diff2
        
        denominator = math.sqrt(denominator1) * math.sqrt(denominator2)
        return numerator / denominator if denominator != 0 else 0.0

    @staticmethod
    def skewness(data):
        n = len(data)
        if n == 0:
            return 0.0
        
        mean = sum(data) / n
        variance = sum((x - mean) ** 2 for x in data) / n
        std_deviation = math.sqrt(variance)
        
        if std_deviation == 0:
            return 0.0
        
        third_moment = sum((x - mean) ** 3 for x in data)
        return n * third_moment / ((n - 1) * (n - 2) * (std_deviation ** 3))

    @staticmethod
    def kurtosis(data):
        n = len(data)
        if n == 0:
            return float('nan')
        
        mean = sum(data) / n
        variance = sum((x - mean) ** 2 for x in data) / n
        std_dev = math.sqrt(variance)
        
        if std_dev == 0:
            return float('nan')
        
        fourth_moment = sum((x - mean) ** 4 for x in data) / n
        return (fourth_moment / (std_dev ** 4)) - 3.0

    @staticmethod
    def pdf(data, mu, sigma):
        sqrt_2pi = math.sqrt(2 * math.pi)
        pdf_values = []
        for x in data:
            exponent = -(x - mu) ** 2 / (2 * sigma ** 2)
            value = (1 / (sigma * sqrt_2pi)) * math.exp(exponent)
            pdf_values.append(value)
        return pdf_values