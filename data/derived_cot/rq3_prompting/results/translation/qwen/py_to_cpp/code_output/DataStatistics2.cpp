#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <stdexcept>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<double>& data) : data(data) {}

    double get_sum() const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double get_min() const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        return *std::min_element(data.begin(), data.end());
    }

    double get_max() const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        return *std::max_element(data.begin(), data.end());
    }

    double get_variance() const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        double mean = get_sum() / data.size();
        double sq_diff_sum = 0.0;
        for (double num : data) {
            double diff = num - mean;
            sq_diff_sum += diff * diff;
        }
        double variance = sq_diff_sum / data.size();
        return std::round(variance * 100.0) / 100.0;
    }

    double get_std_deviation() const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        double variance = get_variance();
        return std::sqrt(variance);
    }

    double get_correlation() const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        return 1.0;
    }
};