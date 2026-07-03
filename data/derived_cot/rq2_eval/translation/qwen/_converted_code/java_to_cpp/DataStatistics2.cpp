#include <vector>
#include <limits>
#include <cmath>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<int>& data) {
        for (int val : data) {
            this->data.push_back(static_cast<double>(val));
        }
    }

    double get_sum() {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double sum = 0.0;
        for (double val : data) {
            sum += val;
        }
        return sum;
    }

    double get_min() {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double min_val = data[0];
        for (double val : data) {
            if (val < min_val) {
                min_val = val;
            }
        }
        return min_val;
    }

    double get_max() {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double max_val = data[0];
        for (double val : data) {
            if (val > max_val) {
                max_val = val;
            }
        }
        return max_val;
    }

    double get_variance() {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double mean = getSum() / data.size();
        double sqDiffSum = 0.0;
        for (double val : data) {
            double diff = val - mean;
            sqDiffSum += diff * diff;
        }
        return sqDiffSum / data.size();
    }

    double get_std_deviation() {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return std::sqrt(getVariance());
    }

    double get_correlation() {
        return 1.0;
    }
};