#include <vector>
#include <cmath>
#include <numeric>
#include <limits>

class DataStatistics4 {
public:
    static double correlationCoefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        int n = static_cast<int>(data1.size());
        double mean1 = 0;
        double mean2 = 0;
        if (n > 0) {
            mean1 = std::accumulate(data1.begin(), data1.end(), 0.0) / n;
            mean2 = std::accumulate(data2.begin(), data2.end(), 0.0) / n;
        }

        double numerator = 0;
        for (int i = 0; i < n; ++i) {
            numerator += (data1[i] - mean1) * (data2[i] - mean2);
        }

        double sum1 = 0;
        for (double x : data1) {
            sum1 += (x - mean1) * (x - mean1);
        }
        double sum2 = 0;
        for (double x : data2) {
            sum2 += (x - mean2) * (x - mean2);
        }

        double denominator = std::sqrt(sum1) * std::sqrt(sum2);

        return denominator != 0 ? numerator / denominator : 0;
    }

    static double skewness(const std::vector<double>& data) {
        int n = static_cast<int>(data.size());
        double mean = 0;
        if (n > 0) {
            mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        }

        double variance = 0;
        if (n > 0) {
            double sum = 0;
            for (double x : data) {
                sum += (x - mean) * (x - mean);
            }
            variance = sum / n;
        }

        double stdDeviation = std::sqrt(variance);

        if (stdDeviation == 0) {
            return 0;
        }

        double sumCubed = 0;
        for (double x : data) {
            sumCubed += (x - mean) * (x - mean) * (x - mean);
        }

        double skewness_val = sumCubed * n / ((n - 1) * (n - 2) * std::pow(stdDeviation, 3));

        return skewness_val;
    }

    static double kurtosis(const std::vector<double>& data) {
        int n = static_cast<int>(data.size());
        double mean = 0;
        if (n > 0) {
            mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        }

        double variance = 0;
        if (n > 0) {
            double sum = 0;
            for (double x : data) {
                sum += (x - mean) * (x - mean);
            }
            variance = sum / n;
        }
        double stdDev = std::sqrt(variance);

        if (stdDev == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        std::vector<double> centeredData(n);
        for (int i = 0; i < n; ++i) {
            centeredData[i] = data[i] - mean;
        }

        double fourthMoment = 0;
        if (n > 0) {
            double sum = 0;
            for (double x : centeredData) {
                sum += std::pow(x, 4);
            }
            fourthMoment = sum / n;
        }

        double kurtosisValue = (fourthMoment / std::pow(stdDev, 4)) - 3;

        return kurtosisValue;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        const double PI = std::acos(-1.0);
        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            result.push_back((1.0 / (sigma * std::sqrt(2 * PI))) * std::exp(-0.5 * std::pow((x - mu) / sigma, 2)));
        }
        return result;
    }
};