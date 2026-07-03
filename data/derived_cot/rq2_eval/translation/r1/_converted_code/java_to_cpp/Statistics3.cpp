#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <optional>
#include <stdexcept>
#include <limits>

class Statistics3 {
public:
    double median(const std::vector<int>& data) {
        if (data.empty()) {
            throw std::out_of_range("median of empty array");
        }
        std::vector<int> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        size_t n = sortedData.size();
        if (n % 2 == 1) {
            return sortedData[n / 2];
        } else {
            return (sortedData[n / 2 - 1] + sortedData[n / 2]) / 2.0;
        }
    }

    std::vector<int> mode(const std::vector<int>& data) {
        if (data.empty()) {
            throw std::runtime_error("mode of empty array");
        }
        std::unordered_map<int, size_t> counts;
        for (int num : data) {
            counts[num]++;
        }
        size_t maxCount = 0;
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

    std::optional<double> correlation(const std::vector<int>& x, const std::vector<int>& y) {
        if (x.size() != y.size() || x.empty()) {
            return std::nullopt;
        }
        auto opt_meanX = mean(x);
        auto opt_meanY = mean(y);
        double meanX = *opt_meanX;
        double meanY = *opt_meanY;

        double numerator = 0.0;
        double denomX = 0.0;
        double denomY = 0.0;

        for (size_t i = 0; i < x.size(); i++) {
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

    std::optional<double> mean(const std::vector<int>& data) {
        if (data.empty()) {
            return std::nullopt;
        }
        double sum = 0.0;
        for (int num : data) {
            sum += num;
        }
        return sum / data.size();
    }

    std::vector<std::vector<double>> correlationMatrix(const std::vector<std::vector<int>>& data) {
        if (data.empty()) {
            throw std::out_of_range("data is empty");
        }
        size_t numRows = data.size();
        size_t numCols = data[0].size();
        for (const auto& row : data) {
            if (row.size() != numCols) {
                throw std::out_of_range("rows have different lengths");
            }
        }

        std::vector<std::vector<double>> matrix(numCols, std::vector<double>(numCols, 0.0));
        for (size_t i = 0; i < numCols; i++) {
            for (size_t j = 0; j < numCols; j++) {
                std::vector<int> col_i;
                std::vector<int> col_j;
                col_i.reserve(numRows);
                col_j.reserve(numRows);
                for (size_t k = 0; k < numRows; k++) {
                    col_i.push_back(data[k][i]);
                    col_j.push_back(data[k][j]);
                }
                auto corr = correlation(col_i, col_j);
                if (corr) {
                    matrix[i][j] = *corr;
                } else {
                    matrix[i][j] = std::numeric_limits<double>::quiet_NaN();
                }
            }
        }
        return matrix;
    }

    std::optional<double> standardDeviation(const std::vector<int>& data) {
        if (data.size() < 2) {
            return std::nullopt;
        }
        auto opt_mean = mean(data);
        double m = *opt_mean;
        double variance = 0.0;
        for (int num : data) {
            variance += std::pow(num - m, 2);
        }
        variance /= (data.size() - 1);
        return std::sqrt(variance);
    }

    std::optional<std::vector<double>> zScore(const std::vector<int>& data) {
        auto opt_mean = mean(data);
        auto opt_stdDev = standardDeviation(data);
        if (!opt_mean || !opt_stdDev || *opt_stdDev == 0) {
            return std::nullopt;
        }
        double m = *opt_mean;
        double stdDev = *opt_stdDev;
        std::vector<double> result;
        result.reserve(data.size());
        for (int num : data) {
            result.push_back((num - m) / stdDev);
        }
        return result;
    }
};