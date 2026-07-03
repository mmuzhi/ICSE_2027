#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <optional>
#include <numeric>

class Statistics3 {
public:
    static std::optional<double> median(const std::vector<double>& data) {
        if (data.empty()) return std::nullopt;
        std::vector<double> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());
        int n = sorted_data.size();
        if (n % 2 == 1) {
            return sorted_data[n / 2];
        } else {
            return (sorted_data[n / 2 - 1] + sorted_data[n / 2]) / 2.0;
        }
    }

    static std::vector<double> mode(const std::vector<double>& data) {
        std::map<double, int> counts;
        std::vector<double> insertion_order;
        for (double value : data) {
            if (counts.find(value) == counts.end()) {
                insertion_order.push_back(value);
            }
            counts[value]++;
        }
        int max_count = 0;
        for (const auto& [value, count] : counts) {
            if (count > max_count) max_count = count;
        }
        std::vector<double> mode_values;
        for (double value : insertion_order) {
            if (counts[value] == max_count) {
                mode_values.push_back(value);
            }
        }
        return mode_values;
    }

    static std::optional<double> correlation(const std::vector<double>& x, const std::vector<double>& y) {
        int n = x.size();
        double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / n;
        double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / n;
        double numerator = 0.0;
        for (int i = 0; i < n; i++) {
            numerator += (x[i] - mean_x) * (y[i] - mean_y);
        }
        double sum_x = 0.0, sum_y = 0.0;
        for (int i = 0; i < n; i++) {
            sum_x += std::pow(x[i] - mean_x, 2);
            sum_y += std::pow(y[i] - mean_y, 2);
        }
        double denominator = std::sqrt(sum_x * sum_y);
        if (denominator == 0) {
            return std::nullopt;
        }
        return numerator / denominator;
    }

    static std::optional<double> mean(const std::vector<double>& data) {
        if (data.empty()) {
            return std::nullopt;
        }
        return std::accumulate(data.begin(), data.end(), 0.0) / static_cast<double>(data.size());
    }

    static std::vector<std::vector<std::optional<double>>> correlation_matrix(const std::vector<std::vector<double>>& data) {
        int num_cols = data[0].size();
        std::vector<std::vector<std::optional<double>>> matrix(num_cols, std::vector<std::optional<double>>(num_cols));
        for (int i = 0; i < num_cols; i++) {
            for (int j = 0; j < num_cols; j++) {
                std::vector<double> column1, column2;
                for (const auto& row : data) {
                    column1.push_back(row[i]);
                    column2.push_back(row[j]);
                }
                matrix[i][j] = correlation(column1, column2);
            }
        }
        return matrix;
    }

    static std::optional<double> standard_deviation(const std::vector<double>& data) {
        int n = data.size();
        if (n < 2) {
            return std::nullopt;
        }
        double mean_value = mean(data).value();
        double variance = 0.0;
        for (double x : data) {
            variance += std::pow(x - mean_value, 2);
        }
        variance /= (n - 1);
        return std::sqrt(variance);
    }

    static std::optional<std::vector<double>> z_score(const std::vector<double>& data) {
        double mean_val = mean(data).value();
        auto std_dev = standard_deviation(data);
        if (!std_dev.has_value() || std_dev.value() == 0) {
            return std::nullopt;
        }
        double sd = std_dev.value();
        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            result.push_back((x - mean_val) / sd);
        }
        return result;
    }
};