#include <cmath>
#include <vector>
#include <numeric>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DataStatistics4 {
public:
    static double correlation_coefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        size_t n = data1.size();
        double mean1 = std::accumulate(data1.begin(), data1.end(), 0.0) / n;
        double mean2 = std::accumulate(data2.begin(), data2.end(), 0.0) / n;

        double numerator = 0.0;
        double sum_sq1 = 0.0;
        double sum_sq2 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff1 = data1[i] - mean1;
            double diff2 = data2[i] - mean2;
            numerator += diff1 * diff2;
            sum_sq1 += diff1 * diff1;
            sum_sq2 += diff2 * diff2;
        }
        double denominator = std::sqrt(sum_sq1) * std::sqrt(sum_sq2);
        if (denominator == 0.0) {
            return 0.0;
        }
        return numerator / denominator;
    }

    static double skewness(const std::vector<double>& data) {
        size_t n = data.size();
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;

        double variance = 0.0;
        double sum_cube = 0.0;
        for (double x : data) {
            double diff = x - mean;
            variance += diff * diff;
            sum_cube += diff * diff * diff;
        }
        variance /= n;
        double std_dev = std::sqrt(variance);

        if (std_dev == 0.0) {
            return 0.0;
        }
        double skewness = (sum_cube * n) / ((n - 1) * (n - 2) * std_dev * std_dev * std_dev);
        return skewness;
    }

    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;

        double variance = 0.0;
        double fourth_moment = 0.0;
        for (double x : data) {
            double diff = x - mean;
            variance += diff * diff;
            fourth_moment += diff * diff * diff * diff;
        }
        variance /= n;
        double std_dev = std::sqrt(variance);

        if (std_dev == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        fourth_moment /= n;
        double kurtosis_value = (fourth_moment / (std_dev * std_dev * std_dev * std_dev)) - 3.0;
        return kurtosis_value;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        double inv_sigma = 1.0 / sigma;
        double inv_sqrt_2pi = 1.0 / std::sqrt(2.0 * M_PI);
        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            double z = (x - mu) * inv_sigma;
            double val = inv_sigma * inv_sqrt_2pi * std::exp(-0.5 * z * z);
            result.push_back(val);
        }
        return result;
    }
};