#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <stdexcept>

class DataStatistics {
public:
    float mean(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::runtime_error("Cannot compute mean for empty data");
        }
        double sum = 0.0;
        for (double num : data) {
            sum += num;
        }
        double mean_value = sum / static_cast<double>(data.size());
        double rounded_mean = std::round(mean_value * 100.0) / 100.0;
        return static_cast<float>(rounded_mean);
    }

    float median(std::vector<double> data) {
        if (data.empty()) {
            throw std::runtime_error("Cannot compute median for empty data");
        }
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 0) {
            size_t middle = n / 2;
            double median_value = (data[middle - 1] + data[middle]) / 2.0;
            double rounded_median = std::round(median_value * 100.0) / 100.0;
            return static_cast<float>(rounded_median);
        } else {
            size_t middle = n / 2;
            double median_value = data[middle];
            double rounded_median = std::round(median_value * 100.0) / 100.0;
            return static_cast<float>(rounded_median);
        }
    }

    std::vector<float> mode(std::vector<double> data) {
        if (data.empty()) {
            throw std::runtime_error("Cannot compute mode for empty data");
        }
        std::map<double, int> counter;
        for (double num : data) {
            counter[num]++;
        }
        if (counter.empty()) {
            throw std::runtime_error("Cannot compute mode for empty data");
        }
        int mode_count = 0;
        for (const auto& pair : counter) {
            if (pair.second > mode_count) {
                mode_count = pair.second;
            }
        }
        std::vector<float> mode_values;
        for (const auto& pair : counter) {
            if (pair.second == mode_count) {
                mode_values.push_back(static_cast<float>(pair.first));
            }
        }
        return mode_values;
    }
};