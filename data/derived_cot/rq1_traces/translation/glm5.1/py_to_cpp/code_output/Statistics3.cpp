#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <optional>
#include <stdexcept>

class Statistics3 {
public:
    static double median(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::out_of_range("data is empty");
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
        std::unordered_map<double, int> counts;
        for (double value : data) {
            counts[value]++;
        }
        if (counts.empty()) {
            throw std::invalid_argument("data is empty");
        }
        int max_count = 0;
        for (const auto& pair : counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
            }
        }
        std::vector<double> mode_values;
        std::unordered_set<double> seen;
        for (double value : data) {
            if (seen.find(value) == seen.end()) {
                seen.insert(value);
                if (counts[value] == max_count) {
                    mode_values.push_back(value);
                }
            }
        }
        return mode_values;
    }

    static std::optional<double> correlation(const std::vector<double>& x, const std::vector<double>& y) {
        size_t n = x.size();
        if (n == 0) {
            throw std::runtime_error("division by zero");
        }
        double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / n;
        double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / n;
        
        double numerator = 0.0;
        size_t min_len = std::min(x.size(), y.size());
        for (size_t i = 0; i < min_len; ++i) {
            numerator += (x[i] - mean_x) * (y[i] - mean_y);
        }
        
        double sum_x = 0.0;
        for (double xi : x) {
            sum_x += (xi - mean_x) * (xi - mean_x);
        }
        
        double sum_y = 0.0;
        for (double yi : y) {
            sum_y += (yi - mean_y) * (yi - mean_y);
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
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    static std::vector<std::vector<std::optional<double>>> correlation_matrix(const std::vector<std::vector<double>>& data) {
        std::vector<std::vector<std::optional<double>>> matrix;
        size_t num_cols = data.at(0).size();
        for (size_t i = 0; i < num_cols; ++i) {
            std::vector<std::optional<double>> row;
            for (size_t j = 0; j < num_cols; ++j) {
                std::vector<double> column1;
                std::vector<double> column2;
                for (size_t k = 0; k < data.size(); ++k) {
                    column1.push_back(data.at(k).at(i));
                    column2.push_back(data.at(k).at(j));
                }
                row.push_back(correlation(column1, column2));
            }
            matrix.push_back(row);
        }
        return matrix;
    }

    static std::optional<double> standard_deviation(const std::vector<double>& data) {
        size_t n = data.size();
        if (n < 2) {
            return std::nullopt;
        }
        std::optional<double> mean_opt = mean(data);
        double mean_value = mean_opt.value();
        double variance = 0.0;
        for (double x : data) {
            variance += (x - mean_value) * (x - mean_value);
        }
        variance /= (n - 1);
        return std::sqrt(variance);
    }

    static std::optional<std::vector<double>> z_score(const std::vector<double>& data) {
        std::optional<double> mean_opt = mean(data);
        std::optional<double> std_deviation_opt = standard_deviation(data);
        if (!std_deviation_opt.has_value() || std_deviation_opt.value() == 0) {
            return std::nullopt;
        }
        double mean_val = mean_opt.value();
        double std_dev = std_deviation_opt.value();
        std::vector<double> result;
        for (double x : data) {
            result.push_back((x - mean_val) / std_dev);
        }
        return result;
    }
};