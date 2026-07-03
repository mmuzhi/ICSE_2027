import math
import numpy as np

class DataStatistics4:
    @staticmethod
    def correlation_coefficient(data1, data2):
        n = len(data1)
        if n == 0:
            return float('nan')
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
        if denominator1 == 0 or denominator2 == 0:
            return 0.0
        denominator = math.sqrt(denominator1) * math.sqrt(denominator2)
        return numerator / denominator

    @staticmethod
    def skewness(data):
        n = len(data)
        if n == 0:
            return float('nan')
        mean = sum(data) / n
        variance = sum((x - mean) ** 2 for x in data) / n
        std_deviation = math.sqrt(variance)
        if std_deviation == 0:
            return 0.0
        skewness_val = sum((x - mean) ** 3 for x in data)
        skewness_val *= n / ((n - 1) * (n - 2) * std_deviation ** 3)
        return skewness_val

    @staticmethod
    def kurtosis(data):
        n = len(data)
        if n == 0:
            return float('nan')
        mean = sum(data) / n
        variance = sum((x - mean) ** 2 for x in data) / n
        std_deviation = math.sqrt(variance)
        if std_deviation == 0:
            return float('nan')
        fourth_moment = sum((x - mean) ** 4 for x in data) / n
        kurtosis_val = fourth_moment / (std_deviation ** 4) - 3.0
        return kurtosis_val

    @staticmethod
    def pdf(data, mu, sigma):
        pdf_values = []
        for x in data:
            if sigma == 0:
                if x == mu:
                    pdf_values.append(float('inf'))
                else:
                    pdf_values.append(0.0)
            else:
                value = (1 / (sigma * math.sqrt(2 * math.pi))) * math.exp(-0.5 * ((x - mu) / sigma) ** 2)
                pdf_values.append(value)
        return pdf_values