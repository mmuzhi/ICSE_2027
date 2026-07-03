#include <vector>
#include <cmath>
#include <numeric>

class DataStatistics4 {
public:
    static double correlationCoefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        int n = static_cast<int>(data1.size());
        double mean1 = average(data1);
        double mean2 = average(data2);

        double numerator = 0;
        for (int i = 0; i < n; i++) {
            numerator += (data1[i] - mean1) * (data2[i] - mean2);
        }

        double sum1 = 0, sum2 = 0;
        for (double x : data1) sum1 += (x - mean1) * (x - mean1);
        for (double x : data2) sum2 += (x - mean2) * (x - mean2);
        double denominator = std::sqrt(sum1) * std::sqrt(sum2);

        return denominator != 0 ? numerator / denominator : 0;
    }

    static double skewness(const std::vector<double>& data) {
        int n = static_cast<int>(data.size());
        double mean = average(data);
        double variance = 0;
        for (double x : data) variance += (x - mean) * (x - mean);
        variance = n > 0 ? variance / n : 0;
        double stdDeviation = std::sqrt(variance);

        if (stdDeviation == 0) {
            return 0;
        }

        double skewness = 0;
        for (double x : data) skewness += (x - mean) * (x - mean) * (x - mean);
        skewness = skewness * n / ((n - 1) * (n - 2) * std::pow(stdDeviation, 3));

        return skewness;
    }

    static double kurtosis(const std::vector<double>& data) {
        int n = static_cast<int>(data.size());
        double mean = average(data);
        double variance = 0;
        for (double x : data) variance += (x - mean) * (x - mean);
        variance = n > 0 ? variance / n : 0;
        double stdDev = std::sqrt(variance);

        if (stdDev == 0) {
            return NAN;
        }

        std::vector<double> centeredData;
        centeredData.reserve(n);
        for (double x : data) centeredData.push_back(x - mean);

        double fourthMoment = 0;
        for (double x : centeredData) fourthMoment += std::pow(x, 4);
        fourthMoment = n > 0 ? fourthMoment / n : 0;

        double kurtosisValue = (fourthMoment / std::pow(stdDev, 4)) - 3;

        return kurtosisValue;
    }

    static std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            result.push_back((1.0 / (sigma * std::sqrt(2.0 * M_PI))) * std::exp(-0.5 * std::pow((x - mu) / sigma, 2)));
        }
        return result;
    }

private:
    static double average(const std::vector<double>& data) {
        if (data.empty()) return 0;
        double sum = 0;
        for (double x : data) sum += x;
        return sum / data.size();
    }
};