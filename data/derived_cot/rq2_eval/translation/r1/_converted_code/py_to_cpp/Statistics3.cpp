#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <optional>
#include <stdexcept>
#include <limits>

class Statistics3 {
public:
    static double median(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::out_of_range("List index out of range");
        }
        std::vector<double> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());
        size_t n = sorted_data.size();
        if (n % 2 == 1) {
            return sorted_data[n / 2];
        } else {
            return (sorted_data[n / 2 - 1] + sorted_data[n / 2]) / 2.0;
        }
    }

    static std::vector<double> mode(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::invalid_argument("max() arg is an empty sequence");
        }
        std::map<double, int> counts;
        for (double value : data) {
            counts[value]++;
        }
        int max_count = 0;
        for (const auto& pair : counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
            }
        }
        std::vector<double> mode_values;
        for (const auto& pair : counts) {
            if (pair.second == max_count) {
                mode_values.push_back(pair.first);
            }
        }
        return mode_values;
    }

    static double correlation(const std::vector<double>& x, const std::vector<double>& y) {
        if (x.size() != y.size()) {
            throw std::invalid_argument("correlation: inputs must have the same length");
        }
        size_t n = x.size();
        if (n == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double sum_x = 0.0;
        double sum_y = 0.0;
        for (size_t i = 0; i < n; ++i) {
            sum_x += x[i];
            sum_y += y[i];
        }
        double mean_x = sum_x / n;
        double mean_y = sum_y / n;

        double numerator = 0.0;
        double denom_x = 0.0;
        double denom_y = 0.0;
        for (size_t i = 0; i < n; ++i) {
            double diff_x = x[i] - mean_x;
            double diff_y = y[i] - mean_y;
            numerator += diff_x * diff_y;
            denom_x += diff_x * diff_x;
            denom_y += diff_y * diff_y;
        }

        double denominator = std::sqrt(denom_x * denom_y);
        if (denominator == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return numerator / denominator;
    }

    static double mean(const std::vector<double>& data) {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double sum = 0.0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    static std::vector<std::vector<double>> correlation_matrix(const std::vector<std::vector<double>>& data) {
        if (data.empty()) {
            return {};
        }
        size_t ncols = data[0].size();
        std::vector<std::vector<double>> matrix(ncols, std::vector<double>(ncols));
        for (size_t i = 0; i < ncols; ++i) {
            for (size_t j = 0; j < ncols; ++j) {
                std::vector<double> col_i;
                std::vector<double> col_j;
                for (const auto& row : data) {
                    if (i < row.size() && j < row.size()) {
                        col_i.push_back(row[i]);
                        col_j.push_back(row[j]);
                    } else {
                        throw std::out_of_range("Index out of range");
                    }
                }
                matrix[i][j] = correlation(col_i, col_j);
            }
        }
        return matrix;
    }

    static double standard_deviation(const std::vector<double>& data) {
        size_t n = data.size();
        if (n < 2) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double mean_val = mean(data);
        double variance = 0.0;
        for (double value : data) {
            variance += (value - mean_val) * (value - mean_val);
        }
        variance /= (n - 1);
        return std::sqrt(variance);
    }

    static std::optional<std::vector<double>> z_score(const std::vector<double>& data) {
        double mean_val = mean(data);
        double std_dev = standard_deviation(data);
        if (std::isnan(std_dev) || std_dev == 0.0) {
            return std::nullopt;
        }
        std::vector<double> result;
        result.reserve(data.size());
        for (double value : data) {
            result.push_back((value - mean_val) / std_dev);
        }
        return result;
    }
};