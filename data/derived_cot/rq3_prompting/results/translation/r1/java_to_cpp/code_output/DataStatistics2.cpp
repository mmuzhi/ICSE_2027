#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <limits>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    explicit DataStatistics2(const std::vector<int>& input) {
        data.reserve(input.size());
        for (int x : input) {
            data.push_back(static_cast<double>(x));
        }
    }

    double getSum() const {
        if (data.empty()) return 0.0;
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double getMin() const {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        return *std::min_element(data.begin(), data.end());
    }

    double getMax() const {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        return *std::max_element(data.begin(), data.end());
    }

    double getVariance() const {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        double mean = getSum() / data.size();
        double sumSq = 0.0;
        for (double val : data) {
            double diff = val - mean;
            sumSq += diff * diff;
        }
        return sumSq / data.size();
    }

    double getStdDeviation() const {
        return std::sqrt(getVariance());
    }

    double getCorrelation() const {
        return 1.0;
    }
};