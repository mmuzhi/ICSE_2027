#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <cmath>

class DataStatistics {
public:
    double mean(const std::vector<double>& data) const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        double sum = 0.0;
        for (double x : data) {
            sum += x;
        }
        double avg = sum / static_cast<double>(data.size());
        return std::round(avg * 100.0) / 100.0;
    }

    double median(const std::vector<double>& data) const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        std::vector<double> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());
        size_t n = sorted_data.size();
        double result;
        if (n % 2 == 0) {
            size_t mid = n / 2;
            result = (sorted_data[mid-1] + sorted_data[mid]) / 2.0;
        } else {
            result = sorted_data[n/2];
        }
        return std::round(result * 100.0) / 100.0;
    }

    std::vector<double> mode(const std::vector<double>& data) const {
        if (data.empty()) {
            throw std::invalid_argument("Data cannot be empty");
        }
        std::unordered_map<double, int> counts;
        std::vector<double> order;
        for (double x : data) {
            if (counts.find(x) == counts.end()) {
                counts[x] = 1;
                order.push_back(x);
            } else {
                counts[x]++;
            }
        }
        int max_count = 0;
        for (const auto& pair : counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
            }
        }
        std::vector<double> modes;
        for (double x : order) {
            if (counts[x] == max_count) {
                modes.push_back(x);
            }
        }
        return modes;
    }
};