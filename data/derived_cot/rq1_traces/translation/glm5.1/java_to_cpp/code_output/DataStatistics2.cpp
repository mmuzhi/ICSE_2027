#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <limits>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<int>& input) {
        // Equivalent to data.stream().mapToDouble(Integer::doubleValue).toArray()
        data.assign(input.begin(), input.end());
    }

    double getSum() const {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double getMin() const {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return *std::min_element(data.begin(), data.end());
    }

    double getMax() const {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return *std::max_element(data.begin(), data.end());
    }

    double getVariance() const {
        if (data.empty()) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double mean = getSum() / data.size();
        double sq_diff_sum = std::accumulate(data.begin(), data.end(), 0.0,
            [mean](double acc, double val) {
                double diff = val - mean;
                return acc + diff * diff;
            });
        return sq_diff_sum / data.size();
    }

    double getStdDeviation() const {
        return std::sqrt(getVariance());
    }

    double getCorrelation() const {
        return 1.0;
    }
};