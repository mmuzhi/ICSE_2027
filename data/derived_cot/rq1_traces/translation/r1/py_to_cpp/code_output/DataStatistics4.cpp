#include <cmath>
#include <vector>
#include <stdexcept>
#include <limits>

class DataStatistics4 {
public:
    static double correlation_coefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        size_t n = data1.size();
        if (n == 0) {
            throw std::invalid_argument("Data must not be empty");
        }
        if (n != data2.size()) {
            throw std::invalid_argument("Data sets must have the same size");
        }

        double mean1 = 0.0;
        double mean2 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mean1 += data1[i];
            mean2 += data2[i];
        }
        mean1 /= n;
        mean2 /= n;

        double numerator = 0.0;
        double denom1 = 0.0;
        double denom2 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff1 = data1[i] - mean1;
            double diff2 = data2[i] - mean2;
            numerator += diff1 * diff2;
            denom1 += diff1 * diff1;
            denom2 += diff2 * diff2;
        }

        double denominator = std::sqrt(denom1) * std::sqrt(denom2);
        if (denominator == 0) {
            return 0.0;
        }
        return numerator / denominator;
    }

    static double skewness(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) {
            throw std::invalid_argument("Data must not be empty");
        }

        double mean = 0.0;
        for (double x : data) {
            mean += x;
        }
        mean /= n;

        double variance = 0.0;
        for (double x : data) {
            double diff = x - mean;
            variance += diff * diff;
        }
        variance /= n;

        double std_deviation = std::sqrt(variance);
        if (std_deviation == 0) {
            return 0.0;
        }

        double sum_cubes = 0.0;
        for (double x : data) {
            double diff = x - mean;
            sum_cubes += diff * diff * diff;
        }

        double numerator = sum_cubes * n;
        double denominator = (n - 1) * (n - 2) * std_deviation * std_deviation * std_deviation;

        return numerator / denominator;
    }

    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) {
            throw std::invalid_argument("Data must not be empty");
        }

        double mean = 0.0;
        for (double x : data) {
            mean += x;
        }
        mean /= n;

        double variance = 0.0;
        for (double x : data) {
            double diff = x - mean;
            variance += diff * diff;
        }
        variance /= n;

        double std_dev = std::sqrt(variance);
        if (std_dev == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double fourth_moment = 0.0;
        for (double x : data) {
            double diff = x - mean;
            fourth_moment += diff * diff * diff * diff;
        }
        fourth_moment /= n;

        double kurtosis_value = fourth_moment / (std_dev * std_dev * std_dev * std_dev) - 3.0;
        return kurtosis_value;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        std::vector<double> result;
        if (data.empty()) {
            return result;
        }

        static constexpr double PI = 3.141592653589793;
        double norm_factor = 1.0 / (sigma * std::sqrt(2.0 * PI));

        for (double x : data) {
            double z = (x - mu) / sigma;
            double exponent = -0.5 * z * z;
            double value = norm_factor * std::exp(exponent);
            result.push_back(value);
        }

        return result;
    }
};