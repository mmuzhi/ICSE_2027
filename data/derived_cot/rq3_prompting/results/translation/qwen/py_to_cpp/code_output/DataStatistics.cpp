#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <stdexcept>

template <typename T>
class DataStatistics {
public:
    double mean(std::vector<T> data) {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty for mean calculation.");
        }
        double sum = 0.0;
        for (const auto& num : data) {
            sum += static_cast<double>(num);
        }
        double average = sum / static_cast<double>(data.size());
        return std::round(average * 100.0) / 100.0;
    }

    double median(std::vector<T> data) {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty for median calculation.");
        }
        std::sort(data.begin(), data.end());
        int n = data.size();
        if (n % 2 == 0) {
            int middle = n / 2;
            double mid_value = (data[middle - 1] + data[middle]) / 2.0;
            return std::round(mid_value * 100.0) / 100.0;
        } else {
            int middle = n / 2;
            return data[middle];
        }
    }

    std::vector<T> mode(std::vector<T> data) {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty for mode calculation.");
        }
        std::map<T, int> counter;
        for (const auto& num : data) {
            counter[num]++;
        }
        int mode_count = 0;
        for (const auto& pair : counter) {
            if (pair.second > mode_count) {
                mode_count = pair.second;
            }
        }
        std::vector<T> mode_values;
        for (const auto& pair : counter) {
            if (pair.second == mode_count) {
                mode_values.push_back(pair.first);
            }
        }
        return mode_values;
    }
};