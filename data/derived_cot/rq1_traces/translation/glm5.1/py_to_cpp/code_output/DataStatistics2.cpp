#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<double>& data) : data(data) {}

    double get_sum() const {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double get_min() const {
        return *std::min_element(data.begin(), data.end());
    }

    double get_max() const {
        return *std::max_element(data.begin(), data.end());
    }

    double get_variance() const {
        double mean = get_sum() / static_cast<double>(data.size());
        double sum_sq_diff = 0.0;
        for (double x : data) {
            sum_sq_diff += (x - mean) * (x - mean);
        }
        double var = sum_sq_diff / static_cast<double>(data.size());
        return std::round(var * 100.0) / 100.0;
    }

    double get_std_deviation() const {
        double mean = get_sum() / static_cast<double>(data.size());
        double sum_sq_diff = 0.0;
        for (double x : data) {
            sum_sq_diff += (x - mean) * (x - mean);
        }
        double std_dev = std::sqrt(sum_sq_diff / static_cast<double>(data.size()));
        return std::round(std_dev * 100.0) / 100.0;
    }

    double get_correlation() const {
        return 1.0;
    }
};