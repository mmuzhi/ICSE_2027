#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<int>& input) {
        data.reserve(input.size());
        for (int val : input) {
            data.push_back(static_cast<double>(val));
        }
    }

    double get_sum() const {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double get_min() const {
        if (data.empty()) {
            return std::nan("");
        }
        return *std::min_element(data.begin(), data.end());
    }

    double get_max() const {
        if (data.empty()) {
            return std::nan("");
        }
        return *std::max_element(data.begin(), data.end());
    }

    double get_variance() const {
        if (data.empty()) {
            return std::nan("");
        }
        double mean = getSum() / data.size();
        double sum_sq = 0.0;
        for (double val : data) {
            double diff = val - mean;
            sum_sq += diff * diff;
        }
        return sum_sq / data.size();
    }

    double get_std_deviation() const {
        return std::sqrt(getVariance());
    }

    double get_correlation() const {
        return 1.0;
    }
};