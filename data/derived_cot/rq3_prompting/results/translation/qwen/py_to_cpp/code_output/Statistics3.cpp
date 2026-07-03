#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <iostream>
#include <utility> // for std::pair

class Statistics3 {
public:
    static float median(std::vector<float> data) {
        std::sort(data.begin(), data.end());
        int n = data.size();
        if (n % 2 == 1) {
            return data[n / 2];
        } else {
            return (data[n / 2 - 1] + data[n / 2]) / 2.0f;
        }
    }

    static std::vector<float> mode(std::vector<float> data) {
        std::unordered_map<float, int> counts;
        for (float value : data) {
            counts[value]++;
        }
        if (counts.empty()) {
            return {};
        }
        int max_count = 0;
        for (const auto& pair : counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
            }
        }
        std::vector<float> mode_values;
        for (const auto& pair : counts) {
            if (pair.second == max_count) {
                mode_values.push_back(pair.first);
            }
        }
        return mode_values;
    }

    static float correlation(const std::vector<float>& x, const std::vector<float>& y) {
        int n = x.size();
        if (n != y.size() || n == 0) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        float sum_x = 0.0f, sum_y = 0.0f;
        for (int i = 0; i < n; i++) {
            sum_x += x[i];
            sum_y += y[i];
        }
        float mean_x = sum_x / n;
        float mean_y = sum_y / n;
        float numerator = 0.0f, sum_x_sq = 0.0f, sum_y_sq = 0.0f;
        for (int i = 0; i < n; i++) {
            numerator += (x[i] - mean_x) * (y[i] - mean_y);
            sum_x_sq += (x[i] - mean_x) * (x[i] - mean_x);
            sum_y_sq += (y[i] - mean_y) * (y[i] - mean_y);
        }
        if (sum_x_sq <= 0.0f || sum_y_sq <= 0.0f) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        float denominator = std::sqrt(sum_x_sq * sum_y_sq);
        return numerator / denominator;
    }

    static float mean(const std::vector<float>& data) {
        int n = data.size();
        if (n == 0) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        float sum = 0.0f;
        for (float value : data) {
            sum += value;
        }
        return sum / n;
    }

    static std::vector<std::vector<float>> correlation_matrix(const std::vector<std::vector<float>>& data) {
        int rows = data.size();
        if (rows == 0) {
            return {};
        }
        int cols = data[0].size();
        std::vector<std::vector<float>> matrix;
        for (int i = 0; i < cols; i++) {
            std::vector<float> col_i;
            for (int r = 0; r < rows; r++) {
                col_i.push_back(data[r][i]);
            }
            for (int j = 0; j < cols; j++) {
                std::vector<float> col_j;
                for (int r = 0; r < rows; r++) {
                    col_j.push_back(data[r][j]);
                }
                float corr = correlation(col_i, col_j);
                matrix[i][j] = corr;
            }
            matrix.push_back(std::vector<float>());
            for (int j = 0; j < cols; j++) {
                matrix.back().push_back(correlation(col_i, col_j));
            }
        }
        return matrix;
    }

    static float standard_deviation(const std::vector<float>& data) {
        int n = data.size();
        if (n < 2) {
            return std::numeric_limits<float>::quiet_NaN();
        }
        float mean_value = mean(data);
        float sum_squares = 0.0f;
        for (float x : data) {
            sum_squares += (x - mean_value) * (x - mean_value);
        }
        float variance = sum_squares / (n - 1);
        return std::sqrt(variance);
    }

    static std::vector<float> z_score(const std::vector<float>& data) {
        float mean_val = mean(data);
        float std_dev = standard_deviation(data);
        if (std::isnan(std_dev)) {
            return std::vector<float>(data.size(), std::numeric_limits<float>::quiet_NaN());
        }
        std::vector<float> result;
        result.reserve(data.size());
        for (float x : data) {
            result.push_back((x - mean_val) / std_dev);
        }
        return result;
    }
};