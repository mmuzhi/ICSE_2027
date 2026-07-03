#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <numeric>

class DataStatistics {
public:
    double mean(const std::vector<double>& data) {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double avg = sum / static_cast<double>(data.size());
        return std::round(avg * 100.0) / 100.0;
    }

    double median(const std::vector<double>& data) {
        std::vector<double> sorted = data;
        std::sort(sorted.begin(), sorted.end());
        size_t n = sorted.size();
        if (n % 2 == 0) {
            size_t mid = n / 2;
            double med = (sorted[mid - 1] + sorted[mid]) / 2.0;
            return std::round(med * 100.0) / 100.0;
        } else {
            size_t mid = n / 2;
            return sorted[mid];  // no rounding, matches Python behavior
        }
    }

    std::vector<double> mode(const std::vector<double>& data) {
        if (data.empty()) return {};
        std::unordered_map<double, int> counter;
        for (double x : data) {
            ++counter[x];
        }
        int max_count = 0;
        for (const auto& p : counter) {
            if (p.second > max_count) max_count = p.second;
        }
        std::vector<double> result;
        for (const auto& p : counter) {
            if (p.second == max_count) {
                result.push_back(p.first);
            }
        }
        return result;
    }
};