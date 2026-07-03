#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <stdexcept>

class DataStatistics {
public:
    double mean(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::runtime_error("Division by zero");
        }
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return std::round((sum / data.size()) * 100.0) / 100.0;
    }

    double median(std::vector<double> data) {
        if (data.empty()) {
            throw std::out_of_range("Index out of range");
        }
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        size_t middle = n / 2;
        if (n % 2 == 0) {
            return std::round(((data[middle - 1] + data[middle]) / 2.0) * 100.0) / 100.0;
        } else {
            return data[middle];
        }
    }

    std::vector<double> mode(const std::vector<double>& data) {
        std::unordered_map<double, int> counter;
        std::vector<double> keys;
        for (double x : data) {
            if (counter.find(x) == counter.end()) {
                keys.push_back(x);
            }
            counter[x]++;
        }
        
        int max_count = 0;
        for (const auto& pair : counter) {
            if (pair.second > max_count) {
                max_count = pair.second;
            }
        }
        
        std::vector<double> res;
        for (double x : keys) {
            if (counter[x] == max_count) {
                res.push_back(x);
            }
        }
        return res;
    }
};