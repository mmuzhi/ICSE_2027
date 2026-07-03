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

    double getSum() const {
        return std::accumulate(data.begin(), data.end(), 0.0);
    }

    double getMin() const {
        if (data.empty()) {
            return std::nan("");
        }
        return *std::min_element(data.begin(), data.end());
    }

    double getMax() const {
        if (data.empty()) {
            return std::nan("");
        }
        return *std::max_element(data.begin(), data.end());
    }

    double getVariance() const {
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

    double getStdDeviation() const {
        return std::sqrt(getVariance());
    }

    double getCorrelation() const {
        return 1.0;
    }
};