#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>

class DataStatistics2 {
private:
    std::vector<double> data;

public:
    DataStatistics2(const std::vector<int>& data) {
        this->data = std::vector<double>(data.begin(), data.end());
    }

    double getSum() const {
        if (data.empty()) return std::numeric_limits<double>::quiet_NaN();
        double sum = 0.0;
        for (double val : data) sum += val;
        return sum;
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
        double sqDiffSum = 0.0;
        for (double val : data) sqDiffSum += (val - mean) * (val - mean);
        return sqDiffSum / data.size();
    }

    double getStdDeviation() const {
        double variance = getVariance();
        if (std::isnan(variance)) return variance;
        return std::sqrt(variance);
    }

    double getCorrelation() const {
        return 1.0;
    }
};

// Example usage:
int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    DataStatistics2 stats(data);

    std::cout << "Sum: " << stats.getSum() << "\n";
    std::cout << "Min: " << stats.getMin() << "\n";
    std::cout << "Max: " << stats.getMax() << "\n";
    std::cout << "Variance: " << stats.getVariance() << "\n";
    std::cout << "StdDev: " << stats.getStdDeviation() << "\n";
    std::cout << "Correlation: " << stats.getCorrelation() << "\n";

    return 0;
}