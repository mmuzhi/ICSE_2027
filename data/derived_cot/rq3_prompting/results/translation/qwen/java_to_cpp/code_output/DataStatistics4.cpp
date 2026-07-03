#include <vector>
#include <cmath>
#include <numeric>
#include <limits>
#include <stdexcept>

double correlationCoefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
    if (data1.size() != data2.size()) {
        throw std::out_of_range("Data lists must be of the same size");
    }

    size_t n = data1.size();
    double mean1 = std::accumulate(data1.begin(), data1.end(), 0.0) / n;
    double mean2 = std::accumulate(data2.begin(), data2.end(), 0.0) / n;

    double numerator = 0.0;
    for (size_t i = 0; i < n; ++i) {
        numerator += (data1[i] - mean1) * (data2[i] - mean2);
    }

    double variance1 = 0.0;
    for (size_t i = 0; i < n; ++i) {
        variance1 += (data1[i] - mean1) * (data1[i] - mean1);
    }
    double stdDev1 = std::sqrt(variance1);

    double variance2 = 0.0;
    for (size_t i = 0; i < n; ++i) {
        variance2 += (data2[i] - mean2) * (data2[i] - mean2);
    }
    double stdDev2 = std::sqrt(variance2);

    double denominator = stdDev1 * stdDev2;

    if (denominator == 0) {
        return 0.0;
    }

    return numerator / denominator;
}

double skewness(const std::vector<double>& data) {
    if (data.empty()) {
        return 0.0;
    }

    size_t n = data.size();
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;

    double variance = 0.0;
    for (size_t i = 0; i < n; ++i) {
        variance += (data[i] - mean) * (data[i] - mean);
    }
    variance /= n;

    if (variance == 0) {
        return 0.0;
    }

    double stdDeviation = std::sqrt(variance);

    double sumOfCubedDeviations = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sumOfCubedDeviations += (data[i] - mean) * (data[i] - mean) * (data[i] - mean);
    }

    double skewness = sumOfCubedDeviations * n / ((n - 1) * (n - 2) * std::pow(stdDeviation, 3));

    return skewness;
}

double kurtosis(const std::vector<double>& data) {
    if (data.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    size_t n = data.size();
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;

    double stdDev = 0.0;
    for (size_t i = 0; i < n; ++i) {
        stdDev += (data[i] - mean) * (data[i] - mean);
    }
    stdDev /= n;
    stdDev = std::sqrt(stdDev);

    if (stdDev == 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double fourthMoment = 0.0;
    for (size_t i = 0; i < n; ++i) {
        fourthMoment += std::pow(data[i] - mean, 4);
    }
    fourthMoment /= n;

    double kurtosisValue = (fourthMoment / std::pow(stdDev, 4)) - 3;

    return kurtosisValue;
}

std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
    if (sigma == 0.0) {
        throw std::domain_error("sigma must be non-zero");
    }

    std::vector<double> result;
    result.reserve(data.size());
    static const double twoPI = 2.0 * M_PI;

    for (double x : data) {
        double exponent = -0.5 * std::pow((x - mu) / sigma, 2);
        double value = (1.0 / (sigma * std::sqrt(twoPI))) * std::exp(exponent);
        result.push_back(value);
    }

    return result;
}