#include <vector>
#include <cmath>
#include <numeric>
#include <limits>
#include <stdexcept>

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
            double diff1 = data1.at(i) - mean1;
            double diff2 = data2.at(i) - mean2;
            numerator += diff1 * diff2;
            sum1 += diff1 * diff1;
            sum2 += diff2 * diff2;
        }
        
        double denominator = std::sqrt(sum1) * std::sqrt(sum2);
        return denominator != 0.0 ? numerator / denominator : 0.0;
    }
    
    static double skewness(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) throw std::runtime_error("division by zero");
        
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        
        double sum_sq = 0.0;
        double sum_cu = 0.0;
        for (double x : data) {
            double diff = x - mean;
            sum_sq += diff * diff;
            sum_cu += diff * diff * diff;
        }
        
        double variance = sum_sq / n;
        double std_deviation = std::sqrt(variance);
        
        if (std_deviation == 0.0) return 0.0;
        
        double denominator = (n - 1.0) * (n - 2.0) * std_deviation * std_deviation * std_deviation;
        if (denominator == 0.0) throw std::runtime_error("division by zero");
        
        return sum_cu * n / denominator;
    }
    
    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) throw std::runtime_error("division by zero");
        
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        
        double sum_sq = 0.0;
        for (double x : data) {
            double diff = x - mean;
            sum_sq += diff * diff;
        }
        double std_dev = std::sqrt(sum_sq / n);
        
        if (std_dev == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        
        double fourth_moment = 0.0;
        for (double x : data) {
            double diff = x - mean;
            fourth_moment += diff * diff * diff * diff;
        }
        fourth_moment /= n;
        
        return (fourth_moment / (std_dev * std_dev * std_dev * std_dev)) - 3.0;
    }
    
    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        if (sigma == 0.0) throw std::runtime_error("division by zero");
        
        std::vector<double> pdf_values;
        pdf_values.reserve(data.size());
        const double pi = 3.14159265358979323846;
        double coeff = 1.0 / (sigma * std::sqrt(2.0 * pi));
        for (double x : data) {
            double diff = (x - mu) / sigma;
            pdf_values.push_back(coeff * std::exp(-0.5 * diff * diff));
        }
        return pdf_values;
    }
};