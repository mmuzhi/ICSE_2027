#include <vector>
#include <algorithm>
#include <cmath>
#include <optional>
#include <limits>
#include <iostream>
#include <map>
#include <unordered_map>
#include <numeric>

namespace org::example {

class Statistics3 {
public:
    double median(std::vector<int> data) {
        std::vector<int> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        int n = sortedData.size();
        if (n % 2 == 1) {
            return sortedData[n / 2];
        } else {
            return (sortedData[n / 2 - 1] + sortedData[n / 2]) / 2.0;
        }
    }

    std::vector<int> mode(std::vector<int> data) {
        std::unordered_map<int, long> counts;
        for (int num : data) {
            counts[num]++;
        }
        long maxCount = 0;
        for (const auto& pair : counts) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
            }
        }
        std::vector<int> modes;
        for (const auto& pair : counts) {
            if (pair.second == maxCount) {
                modes.push_back(pair.first);
            }
        }
        return modes;
    }

    std::optional<double> correlation(std::vector<int> x, std::vector<int> y) {
        if (x.size() != y.size() || x.empty()) {
            return std::nullopt;
        }

        double meanX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
        double meanY = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

        double numerator = 0.0;
        double denomX = 0.0;
        double denomY = 0.0;

        for (size_t i = 0; i < x.size(); ++i) {
            double diffX = x[i] - meanX;
            double diffY = y[i] - meanY;
            numerator += diffX * diffY;
            denomX += diffX * diffX;
            denomY += diffY * diffY;
        }

        if (denomX == 0 || denomY == 0) {
            return std::nullopt;
        }

        return numerator / std::sqrt(denomX * denomY);
    }

    std::optional<double> mean(std::vector<int> data) {
        if (data.empty()) {
            return std::nullopt;
        }
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    std::vector<std::vector<double>> correlationMatrix(std::vector<std::vector<int>> data) {
        int numCols = data[0].size();
        std::vector<std::vector<double>> matrix(numCols, std::vector<double>(numCols));

        for (int i = 0; i < numCols; ++i) {
            std::vector<int> col1;
            for (const auto& row : data) {
                col1.push_back(row[i]);
            }
            for (int j = 0; j < numCols; ++j) {
                std::vector<int> col2;
                for (const auto& row : data) {
                    col2.push_back(row[j]);
                }
                auto corr = correlation(col1, col2);
                matrix[i][j] = corr.has_value() ? *corr : std::numeric_limits<double>::quiet_NaN();
            }
        }

        return matrix;
    }

    std::optional<double> standardDeviation(std::vector<int> data) {
        if (data.size() < 2) {
            return std::nullopt;
        }
        auto meanVal = mean(data);
        if (!meanVal.has_value()) {
            return std::nullopt;
        }
        double variance = 0.0;
        for (int num : data) {
            double diff = num - *meanVal;
            variance += diff * diff;
        }
        variance /= (data.size() - 1);
        return std::sqrt(variance);
    }

    std::optional<std::vector<double>> zScore(std::vector<int> data) {
        auto meanVal = mean(data);
        auto stdDev = standardDeviation(data);
        if (!meanVal.has_value() || !stdDev.has_value() || *stdDev == 0) {
            return std::nullopt;
        }
        std::vector<double> zScores;
        for (int num : data) {
            zScores.push_back((num - *meanVal) / *stdDev);
        }
        return zScores;
    }
};

} // namespace org::example