#include <vector>
#include <cmath>
#include <numeric>
#include <limits>

namespace DataStatistics {

    double correlationCoefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        if (data1.size() != data2.size()) {
            return 0.0;
        }
        double n = data1.size();
        double mean1 = std::accumulate(data1.begin(), data1.end(), 0.0) / n;
        double mean2 = std::accumulate(data2.begin(), data2.end(), 0.0) / n;

        double numerator = 0.0;
        for (size_t i = 0; i < n; ++i) {
            numerator += (data1[i] - mean1) * (data2[i] - mean2);
        }

        double variance1 = 0.0, variance2 = 0.0;
        for (double x : data1) {
            variance1 += (x - mean1) * (x - mean1);
        }
        for (double x : data2) {
            variance2 += (x - mean2) * (x - mean2);
        }

        double denominator = std::sqrt(variance1) * std::sqrt(variance2);
        return denominator != 0.0 ? numerator / denominator : 0.0;
    }

    double skewness(const std::vector<double>& data) {
        if (data.empty()) {
            return 0.0;
        }
        double n = data.size();
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        double variance = 0.0;
        for (double x : data) {
            variance += (x - mean) * (x - mean);
        }
        variance /= n;
        double stdDeviation = std::sqrt(variance);

        if (stdDeviation == 0.0) {
            return 0.0;
        }

        double sumOfCubes = 0.0;
        for (double x : data) {
            sumOfCubes += (x - mean) * (x - mean) * (x - mean);
        }
        double skewness = sumOfCubes * n / ((n - 1.0) * (n - 2.0) * std::pow(stdDeviation, 3.0));
        return skewness;
    }

    double kurtosis(const std::vector<double>& data) {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double n = data.size();
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        double stdDev = 0.0;
        for (double x : data) {
            stdDev += (x - mean) * (x - mean);
        }
        stdDev /= n;
        stdDev = std::sqrt(stdDev);

        if (stdDev == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double fourthMoment = 0.0;
        for (double x : data) {
            double centered = x - mean;
            fourthMoment += centered * centered * centered * centered;
        }
        fourthMoment /= n;

        double kurtosisValue = (fourthMoment / (stdDev * stdDev * stdDev * stdDev)) - 3.0;
        return kurtosisValue;
    }

    std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        std::vector<double> result;
        result.reserve(data.size());
        const double invSigmaSqrt2PI = 1.0 / (sigma * std::sqrt(2.0 * M_PI));
        for (double x : data) {
            result.push_back(invSigmaSqrt2PI * std::exp(-0.5 * std::pow((x - mu) / sigma, 2.0)));
        }
        return result;
    }

} // namespace DataStatistics