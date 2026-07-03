#include <vector>
#include <cmath>
#include <limits>

class DataStatistics4 {
public:
    static double correlation_coefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        size_t n = data1.size();
        if (n != data2.size()) {
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
            numerator += (data1[i] - mean1) * (data2[i] - mean2);
            denom1 += (data1[i] - mean1) * (data1[i] - mean1);
            denom2 += (data2[i] - mean2) * (data2[i] - mean2);
        }

        if (denom1 == 0.0 || denom2 == 0.0) {
            return 0.0;
        }
        double denominator = std::sqrt(denom1) * std::sqrt(denom2);
        return numerator / denominator;
    }

    static double skewness(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) return 0.0;

        double mean = 0.0;
        for (double x : data) mean += x;
        mean /= n;

        double variance = 0.0;
        for (double x : data) variance += (x - mean) * (x - mean);
        variance /= n;

        if (variance == 0.0) return 0.0;

        double std_deviation = std::sqrt(variance);
        double raw_moment_3 = 0.0;
        for (double x : data) raw_moment_3 += std::pow(x - mean, 3);
        raw_moment_3 /= n;

        return (n / ((n - 1) * (n - 2))) * raw_moment_3 / std::pow(std_deviation, 3);
    }

    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) return std::numeric_limits<double>::quiet_NaN();

        double mean = 0.0;
        for (double x : data) mean += x;
        mean /= n;

        double variance = 0.0;
        for (double x : data) variance += (x - mean) * (x - mean);
        variance /= n;
        double std_deviation = std::sqrt(variance);

        if (std_deviation == 0.0) return std::numeric_limits<double>::quiet_NaN();

        double fourth_moment = 0.0;
        for (double x : data) {
            double centered = x - mean;
            fourth_moment += centered * centered * centered * centered;
        }
        fourth_moment /= n;

        double kurtosis_value = (fourth_moment / std::pow(std_deviation, 4)) - 3;
        return kurtosis_value;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        if (sigma <= 0.0) {
            throw std::invalid_argument("Standard deviation must be positive");
        }

        std::vector<double> result;
        const double two_pi = 2.0 * M_PI;
        for (double x : data) {
            double z = (x - mu) / sigma;
            double exponent = -0.5 * z * z;
            result.push_back(std::exp(exponent) / (sigma * std::sqrt(two_pi)));
        }
        return result;
    }
};