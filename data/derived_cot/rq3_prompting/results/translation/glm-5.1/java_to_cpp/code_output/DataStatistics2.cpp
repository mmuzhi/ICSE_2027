#include <vector>
#include <numeric>
#include <cmath>
#include <limits>
#include <algorithm>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<int>& data) {
        this->data.reserve(data.size());
        for (int val : data) {
            this->data.push_back(static_cast<double>(val));
        }
    }

    double getSum() {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double getMin() {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        return *std::min_element(data.begin(), data.end());
    }

    double getMax() {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        return *std::max_element(data.begin(), data.end());
    }

    double getVariance() {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        double mean = getSum() / data.size();
        double sq_diff_sum = std::accumulate(data.begin(), data.end(), 0.0, [mean](double acc, double val) {
            double diff = val - mean;
            return acc + diff * diff;
        });
        return sq_diff_sum / data.size();
    }

    double getStdDeviation() {
        return std::sqrt(getVariance());
    }

    double getCorrelation() {
        return 1.0;
    }
};