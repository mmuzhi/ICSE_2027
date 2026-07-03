#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

namespace DataStatistics4 {

    double correlationCoefficient(const std::vector<double>& data1, const std::vector<double>& data2) {
        int n = data1.size();
        if (n == 0) return 0.0;

        double mean1 = std::accumulate(data1.begin(), data1.end(), 0.0) / n;
        double mean2 = std::accumulate(data2.begin(), data2.end(), 0.0) / n;

        double numerator = 0.0;
        double sumSq1 = 0.0;
        double sumSq2 = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff1 = data1[i] - mean1;
            double diff2 = data2[i] - mean2;
            numerator += diff1 * diff2;
            sumSq1 += diff1 * diff1;
            sumSq2 += diff2 * diff2;
        }

        double denominator = std::sqrt(sumSq1) * std::sqrt(sumSq2);
        return (denominator != 0.0) ? (numerator / denominator) : 0.0;
    }

    double skewness(const std::vector<double>& data) {
        int n = data.size();
        if (n <= 2) return 0.0; // avoid division by zero in formula, but Java code would still compute? For n=0 or 1, variance=0, returns 0. For n=2, denominator (n-1)*(n-2)=0, but if variance!=0, division by zero. However Java's formula uses n/((n-1)*(n-2)), so n=2 leads to division by zero. In Java, if n=2 and stdDev!=0, then division by zero -> NaN? Actually Java's integer division? It's double division, so 2/(1*0) = 2/0 = Infinity. But their earlier check stdDev==0 would not catch that. To keep identical behavior, we should replicate exactly: compute mean, variance, stdDev, if stdDev==0 return 0; else compute skewness sum/((n-1)*(n-2)*stdDev^3) * n. For n=2, (n-1)*(n-2)=0, so division by zero gives inf. We'll keep that.
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        double variance = 0.0;
        for (double x : data) {
            double diff = x - mean;
            variance += diff * diff;
        }
        variance /= n; // population variance
        double stdDev = std::sqrt(variance);
        if (stdDev == 0.0) {
            return 0.0;
        }

        double sumCubed = 0.0;
        for (double x : data) {
            double diff = x - mean;
            sumCubed += diff * diff * diff;
        }

        double skewness = sumCubed * n / ((n - 1) * (n - 2) * std::pow(stdDev, 3));
        return skewness;
    }

    double kurtosis(const std::vector<double>& data) {
        int n = data.size();
        if (n == 0) return std::numeric_limits<double>::quiet_NaN();

        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        double variance = 0.0;
        for (double x : data) {
            double diff = x - mean;
            variance += diff * diff;
        }
        variance /= n;
        double stdDev = std::sqrt(variance);
        if (stdDev == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double fourthMoment = 0.0;
        for (double x : data) {
            double centered = x - mean;
            fourthMoment += std::pow(centered, 4);
        }
        fourthMoment /= n;

        double kurtosisValue = fourthMoment / std::pow(stdDev, 4) - 3.0;
        return kurtosisValue;
    }

    std::vector<double> pdf(const std::vector<double>& data, double mu, double sigma) {
        const double invSqrt2Pi = 1.0 / std::sqrt(2.0 * M_PI);
        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            double z = (x - mu) / sigma;
            double value = (1.0 / sigma) * invSqrt2Pi * std::exp(-0.5 * z * z);
            result.push_back(value);
        }
        return result;
    }

} // namespace DataStatistics4