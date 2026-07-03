#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <cmath>

class DataStatistics {
public:
    double mean(const std::vector<double>& data) {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return std::round(sum / static_cast<double>(data.size()) * 100.0) / 100.0;
    }

    double median(std::vector<double> data) {
        std::sort(data.begin(), data.end());
        int n = static_cast<int>(data.size());
        if (n % 2 == 0) {
            int middle = n / 2;
            return std::round((data[middle - 1] + data[middle]) / 2.0 * 100.0) / 100.0;
        } else {
            int middle = n / 2;
            return data[middle];
        }
    }

    std::vector<double> mode(const std::vector<double>& data) {
        std::unordered_map<double, int> counter;
        for (double x : data) {
            counter[x]++;
        }
        int mode_count = 0;
        for (const auto& p : counter) {
            if (p.second > mode_count) {
                mode_count = p.second;
            }
        }
        std::vector<double> result;
        for (const auto& p : counter) {
            if (p.second == mode_count) {
                result.push_back(p.first);
            }
        }
        return result;
    }
};