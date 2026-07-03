#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <numeric>
#include <limits>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DataStatistics4 {
public:
    static double correlation_coefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        size_t n = data1.size();
        if (n == 0) throw std::runtime_error("division by zero");
        
        double mean1 = std::accumulate(data1.begin(), data1.end(), 0.0) / n;
        double mean2 = std::accumulate(data2.begin(), data2.end(), 0.0) / n;

        double numerator = 0.0;
        double sum1 = 0.0;
        double sum2 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff1 = data1[i] - mean1;
            double diff2 = data2[i] - mean2;
            numerator += diff1 * diff2;
            sum1 += diff1 * diff1;
            sum2 += diff2 * diff2;
        }
        double denominator = std::sqrt(sum1) * std::sqrt(sum2);
        return denominator != 0 ? numerator / denominator : 0.0;
    }
    
    static double skewness(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) throw std::runtime_error("division by zero");
        
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        double variance = 0.0;
        double sum3 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff = data[i] - mean;
            variance += diff * diff;
            sum3 += diff * diff * diff;
        }
        variance /= n;
        double std_deviation = std::sqrt(variance);

        if (std_deviation == 0) return 0.0;
        double denom = (n - 1.0) * (n - 2.0) * std_deviation * std_deviation * std_deviation;
        if (denom == 0) throw std::runtime_error("division by zero");
        return sum3 * n / denom;
    }
    
    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) throw std::runtime_error("division by zero");
        
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        double variance = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff = data[i] - mean;
            variance += diff * diff;
        }
        double std_dev = std::sqrt(variance / n);

        if (std_dev == 0) return std::numeric_limits<double>::quiet_NaN();

        double fourth_moment = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff = data[i] - mean;
            fourth_moment += diff * diff * diff * diff;
        }
        fourth_moment /= n;

        return (fourth_moment / (std_dev * std_dev * std_dev * std_dev)) - 3.0;
    }
    
    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        if (sigma == 0) throw std::runtime_error("division by zero");
        
        std::vector<double> pdf_values;
        pdf_values.reserve(data.size());
        double coeff = 1.0 / (sigma * std::sqrt(2.0 * M_PI));
        for (double x : data) {
            double diff = (x - mu) / sigma;
            pdf_values.push_back(coeff * std::exp(-0.5 * diff * diff));
        }
        return pdf_values;
    }
};