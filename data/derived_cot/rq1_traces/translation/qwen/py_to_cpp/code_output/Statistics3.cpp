#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

class Statistics3 {
public:
    static double median(std::vector<double> data) {
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 1) {
            return data[n / 2];
        } else {
            return (data[n / 2 - 1] + data[n / 2]) / 2.0;
        }
    }

    static std::vector<double> mode(std::vector<double> data) {
        std::map<double, int> counts;
        for (double value : data) {
            counts[value]++;
        }
        int max_count = 0;
        for (auto& pair : counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
            }
        }
        std::vector<double> mode_values;
        for (auto& pair : counts) {
            if (pair.second == max_count) {
                mode_values.push_back(pair.first);
            }
        }
        return mode_values;
    }

    static double correlation(std::vector<double> x, std::vector<double> y) {
        size_t n = x.size();
        if (n != y.size()) {
            throw std::invalid_argument("x and y must have the same length");
        }
        double mean_x = 0.0;
        double mean_y = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mean_x += x[i];
            mean_y += y[i];
        }
        mean_x /= n;
        mean_y /= n;
        double numerator = 0.0;
        double denominator_x = 0.0;
        double denominator_y = 0.0;
        for (size_t i = 0; i < n; ++i) {
            numerator += (x[i] - mean_x) * (y[i] - mean_y);
            denominator_x += (x[i] - mean_x) * (x[i] - mean_x);
            denominator_y += (y[i] - mean_y) * (y[i] - mean_y);
        }
        denominator_x = std::sqrt(denominator_x);
        denominator_y = std::sqrt(denominator_y);
        double denominator = denominator_x * denominator_y;
        if (denominator == 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return numerator / denominator;
    }

    static double mean(std::vector<double> data) {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double sum = 0.0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    static std::vector<std::vector<double>> correlation_matrix(std::vector<std::vector<double>> data) {
        size_t num_columns = data[0].size();
        std::vector<std::vector<double>> matrix;
        for (size_t i = 0; i < num_columns; ++i) {
            std::vector<double> row;
            for (size_t j = 0; j < num_columns; ++j) {
                std::vector<double> col1, col2;
                for (size_t k = 0; k < data.size(); ++k) {
                    col1.push_back(data[k][i]);
                    col2.push_back(data[k][j]);
                }
                row.push_back(correlation(col1, col2));
            }
            matrix.push_back(row);
        }
        return matrix;
    }

    static double standard_deviation(std::vector<double> data) {
        if (data.size() < 2) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double mean_value = mean(data);
        double variance = 0.0;
        for (double x : data) {
            variance += (x - mean_value) * (x - mean_value);
        }
        variance /= (data.size() - 1);
        return std::sqrt(variance);
    }

    static std::vector<double> z_score(std::vector<double> data) {
        double mean = mean(data);
        double std_deviation = standard_deviation(data);
        if (std::isnan(std_deviation) || std_deviation == 0.0) {
            return std::vector<double>();
        }
        std::vector<double> result;
        for (double x : data) {
            result.push_back((x - mean) / std_deviation);
        }
        return result;
    }
};