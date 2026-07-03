#include <vector>
#include <cmath>

class DataStatistics4 {
public:
    static double correlation_coefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        size_t n = data1.size();
        if (data1.size() != data2.size()) {
            throw std::invalid_argument("Data vectors must be of the same length");
        }

        double mean1 = 0.0, mean2 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mean1 += data1[i];
            mean2 += data2[i];
        }
        mean1 /= n;
        mean2 /= n;

        double numerator = 0.0, denom1 = 0.0, denom2 = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff1 = data1[i] - mean1;
            double diff2 = data2[i] - mean2;
            numerator += diff1 * diff2;
            denom1 += diff1 * diff1;
            denom2 += diff2 * diff2;
        }

        if (denom1 == 0 || denom2 == 0) {
            return 0.0;
        }
        return numerator / std::sqrt(denom1 * denom2);
    }

    static double skewness(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) {
            throw std::invalid_argument("Data vector is empty");
        }

        double mean = 0.0;
        for (double x : data) mean += x;
        mean /= n;

        double variance = 0.0;
        for (double x : data) variance += (x - mean) * (x - mean);
        variance /= n;
        double std_deviation = std::sqrt(variance);

        if (std_deviation == 0.0) {
            return 0.0;
        }

        double sum_cubed = 0.0;
        for (double x : data) sum_cubed += (x - mean) * (x - mean) * (x - mean);
        return (n / ((n - 1) * (n - 2))) * (sum_cubed / (std_deviation * std_deviation * std_deviation));
    }

    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) {
            throw std::invalid_argument("Data vector is empty");
        }

        double mean = 0.0;
        for (double x : data) mean += x;
        mean /= n;

        double variance = 0.0;
        for (double x : data) variance += (x - mean) * (x - mean);
        variance /= n;
        double std_dev = std::sqrt(variance);

        if (std_dev == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double fourth_moment = 0.0;
        for (double x : data) fourth_moment += std::pow(x - mean, 4);
        fourth_moment /= n;

        return (fourth_moment / std::pow(std_dev, 4)) - 3;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        std::vector<double> result;
        const double sqrt_two_pi = std::sqrt(2 * M_PI);
        for (double x : data) {
            result.push_back(std::exp(-0.5 * std::pow((x - mu) / sigma, 2)) / (sigma * sqrt_two_pi));
        }
        return result;
    }
};