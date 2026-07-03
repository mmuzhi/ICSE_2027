#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <optional>

class Statistics3 {
public:
    static double median(const std::vector<double>& data) {
        std::vector<double> sorted = data;
        std::sort(sorted.begin(), sorted.end());
        size_t n = sorted.size();
        if (n % 2 == 1) {
            return sorted[n / 2];
        } else {
            return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
        }
    }

    static std::vector<double> mode(const std::vector<double>& data) {
        std::map<double, int> counts;
        for (double value : data) {
            counts[value]++;
        }
        int max_count = 0;
        for (const auto& p : counts) {
            if (p.second > max_count) max_count = p.second;
        }
        std::vector<double> mode_values;
        for (const auto& p : counts) {
            if (p.second == max_count) mode_values.push_back(p.first);
        }
        return mode_values;
    }

    static std::optional<double> correlation(const std::vector<double>& x, const std::vector<double>& y) {
        size_t n = x.size();
        double mean_x = std::accumulate(x.begin(), x.end(), 0.0) / n;
        double mean_y = std::accumulate(y.begin(), y.end(), 0.0) / n;
        double numerator = 0.0;
        for (size_t i = 0; i < n; ++i) {
            numerator += (x[i] - mean_x) * (y[i] - mean_y);
        }
        double sum_sq_x = 0.0, sum_sq_y = 0.0;
        for (double xi : x) sum_sq_x += (xi - mean_x) * (xi - mean_x);
        for (double yi : y) sum_sq_y += (yi - mean_y) * (yi - mean_y);
        double denominator = std::sqrt(sum_sq_x * sum_sq_y);
        if (denominator == 0.0) {
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
        size_t n = data[0].size(); // number of columns
        std::vector<std::vector<std::optional<double>>> matrix(n, std::vector<std::optional<double>>(n));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                std::vector<double> col_i, col_j;
                for (const auto& row : data) {
                    col_i.push_back(row[i]);
                    col_j.push_back(row[j]);
                }
                matrix[i][j] = correlation(col_i, col_j);
            }
        }
        return matrix;
    }

    static std::optional<double> standard_deviation(const std::vector<double>& data) {
        size_t n = data.size();
        if (n < 2) {
            return std::nullopt;
        }
        double mean_val = mean(data).value(); // mean is guaranteed to have value for n>=1
        double variance = 0.0;
        for (double x : data) {
            variance += (x - mean_val) * (x - mean_val);
        }
        variance /= (n - 1);
        return std::sqrt(variance);
    }

    static std::optional<std::vector<double>> z_score(const std::vector<double>& data) {
        auto mean_opt = mean(data);
        if (!mean_opt.has_value()) return std::nullopt;
        double mean_val = mean_opt.value();
        auto std_opt = standard_deviation(data);
        if (!std_opt.has_value() || std_opt.value() == 0.0) {
            return std::nullopt;
        }
        double std_val = std_opt.value();
        std::vector<double> result;
        result.reserve(data.size());
        for (double x : data) {
            result.push_back((x - mean_val) / std_val);
        }
        return result;
    }
};