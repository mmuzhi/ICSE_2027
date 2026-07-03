#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <stdexcept>

class DataStatistics2 {
private:
    std::vector<double> data;

    double round_to_two(double val) {
        return std::round(val * 100.0) / 100.0;
    }

public:
    DataStatistics2(std::vector<double> data) : data(std::move(data)) {}

    double get_sum() {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double get_min() {
        if (data.empty()) throw std::invalid_argument("empty data");
        return *std::min_element(data.begin(), data.end());
    }

    double get_max() {
        if (data.empty()) throw std::invalid_argument("empty data");
        return *std::max_element(data.begin(), data.end());
    }

    double get_variance() {
        if (data.empty()) throw std::invalid_argument("empty data");
        double mean = get_sum() / data.size();
        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
        double variance = sq_sum / data.size() - mean * mean;
        return round_to_two(variance);
    }

    double get_std_deviation() {
        if (data.empty()) throw std::invalid_argument("empty data");
        double mean = get_sum() / data.size();
        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
        double variance = sq_sum / data.size() - mean * mean;
        return round_to_two(std::sqrt(variance));
    }

    double get_correlation() {
        if (data.empty()) throw std::invalid_argument("empty data");
        // For a 1D array, correlation with itself is always 1.0
        return 1.0;
    }
};