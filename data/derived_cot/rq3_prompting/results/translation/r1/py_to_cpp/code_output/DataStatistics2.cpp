#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

class DataStatistics2 {
private:
    std::vector<double> data;

    // Helper: round to two decimal places
    static double round_to_2(double v) {
        return std::round(v * 100.0) / 100.0;
    }

    void check_not_empty() const {
        if (data.empty()) {
            throw std::runtime_error("zero-size array to reduction operation");
        }
    }

public:
    explicit DataStatistics2(const std::vector<double>& input_data)
        : data(input_data) {}

    double get_sum() const {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double get_min() const {
        check_not_empty();
        return *std::min_element(data.begin(), data.end());
    }

    double get_max() const {
        check_not_empty();
        return *std::max_element(data.begin(), data.end());
    }

    double get_variance() const {
        check_not_empty();
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double sum_sq = 0.0;
        for (double x : data) {
            double diff = x - mean;
            sum_sq += diff * diff;
        }
        return round_to_2(sum_sq / data.size());  // population variance
    }

    double get_std_deviation() const {
        double var = get_variance();
        return round_to_2(std::sqrt(var));
    }

    double get_correlation() const {
        // For a single variable, correlation with itself is always 1.0
        return 1.0;
    }
};