import math

pai = 3.141592653589793

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
        
        denominator = math.sqrt(denominator1) * math.sqrt(denominator2)
        if denominator == 0:
            return 0.0
        return numerator / denominator

    @staticmethod
    def skewness(data):
        n = len(data)
        if n == 0:
            return float('nan')
        mean = sum(data) / n
        
        variance = 0.0
        for x in data:
            variance += (x - mean) ** 2
        variance /= n
        std_deviation = math.sqrt(variance)
        
        if std_deviation == 0:
            return 0.0
            
        skewness_val = 0.0
        for x in data:
            skewness_val += (x - mean) ** 3
        
        skewness_val = (n * skewness_val) / ((n - 1) * (n - 2) * (std_deviation ** 3))
        return skewness_val

    @staticmethod
    def kurtosis(data):
        n = len(data)
        if n == 0:
            return float('nan')
        mean = sum(data) / n
        
        variance = 0.0
        for x in data:
            variance += (x - mean) ** 2
        variance /= n
        std_dev = math.sqrt(variance)
        
        if std_dev == 0:
            return float('nan')
            
        fourth_moment = 0.0
        for x in data:
            fourth_moment += (x - mean) ** 4
        fourth_moment /= n
        
        kurtosis_value = fourth_moment / (std_dev ** 4) - 3.0
        return kurtosis_value

    @staticmethod
    def pdf(data, mu, sigma):
        pdf_values = []
        factor = 1.0 / (sigma * math.sqrt(2 * pai))
        for x in data:
            z = (x - mu) / sigma
            value = factor * math.exp(-0.5 * (z ** 2))
            pdf_values.append(value)
        return pdf_values