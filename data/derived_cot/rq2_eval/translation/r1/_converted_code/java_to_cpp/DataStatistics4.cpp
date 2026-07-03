#ifndef DATA_STATISTICS_4_H
#define DATA_STATISTICS_4_H

#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace org_example {

class DataStatistics4 {
public:
    static double correlation_coefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        size_t n = data1.size();
        if (n == 0) {
            return 0.0;
        }

        double mean1 = 0.0;
        double mean2 = 0.0;
        for (size_t i = 0; i < n; i++) {
            mean1 += data1[i];
            mean2 += data2.at(i);
        }
        mean1 /= n;
        mean2 /= n;

        double numerator = 0.0;
        double denom1 = 0.0;
        double denom2 = 0.0;
        for (size_t i = 0; i < n; i++) {
            double diff1 = data1[i] - mean1;
            double diff2 = data2.at(i) - mean2;
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
            return 0.0;
        }

        double mean = 0.0;
        for (double x : data) {
            mean += x;
        }
        mean /= n;

        double variance = 0.0;
        for (double x : data) {
            double dev = x - mean;
            variance += dev * dev;
        }
        variance /= n;

        double stdDev = std::sqrt(variance);
        if (stdDev == 0) {
            return 0.0;
        }

        double sumCubed = 0.0;
        for (double x : data) {
            double dev = x - mean;
            sumCubed += dev * dev * dev;
        }

        double denominator_value = (n-1)*(n-2)*std::pow(stdDev, 3);
        double skewness = (sumCubed * n) / denominator_value;
        return skewness;
    }

    static double kurtosis(const std::vector<double>& data) {
        size_t n = data.size();
        if (n == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double mean = 0.0;
        for (double x : data) {
            mean += x;
        }
        mean /= n;

        double variance = 0.0;
        for (double x : data) {
            double dev = x - mean;
            variance += dev * dev;
        }
        variance /= n;

        double stdDev = std::sqrt(variance);
        if (stdDev == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double fourthMoment = 0.0;
        for (double x : data) {
            double dev = x - mean;
            fourthMoment += dev * dev * dev * dev;
        }
        fourthMoment /= n;

        double kurtosisValue = fourthMoment / (stdDev * stdDev * stdDev * stdDev) - 3.0;
        return kurtosisValue;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        const double pi = std::acos(-1.0);
        double factor = 1.0 / (sigma * std::sqrt(2.0 * pi));

        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            double z = (x - mu) / sigma;
            double density = factor * std::exp(-0.5 * z * z);
            result.push_back(density);
        }
        return result;
    }
};

} // namespace org_example

#endif // DATA_STATISTICS_4_H