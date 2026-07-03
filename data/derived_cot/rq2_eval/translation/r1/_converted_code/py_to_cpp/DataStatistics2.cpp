#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

class DataStatistics2 {
private:
    vector<double> data;

public:
    DataStatistics2(const vector<double>& data) : data(data) {}

    double get_sum() {
        double sum = 0.0;
        for (double x : data) {
            sum += x;
        }
        return sum;
    }

    double get_min() {
        if (data.empty()) {
            return numeric_limits<double>::quiet_NaN();
        }
        return *min_element(data.begin(), data.end());
    }

    double get_max() {
        if (data.empty()) {
            return numeric_limits<double>::quiet_NaN();
        }
        return *max_element(data.begin(), data.end());
    }

    double get_variance() {
        if (data.empty()) {
            return numeric_limits<double>::quiet_NaN();
        }
        double total = get_sum();
        double mean = total / data.size();
        double sq_sum = 0.0;
        for (double x : data) {
            double diff = x - mean;
            sq_sum += diff * diff;
        }
        double variance = sq_sum / data.size();
        variance = round(variance * 100) / 100.0;
        return variance;
    }

    double get_std_deviation() {
        if (data.empty()) {
            return numeric_limits<double>::quiet_NaN();
        }
        double variance = get_variance();
        double std_dev = sqrt(variance);
        std_dev = round(std_dev * 100) / 100.0;
        return std_dev;
    }

    double get_correlation() {
        if (data.empty()) {
            return numeric_limits<double>::quiet_NaN();
        }
        return 1.0;
    }
};