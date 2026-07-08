#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>

class DataStatistics {
public:
    double mean(const std::vector<int>& data) {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return std::round((sum / data.size()) * 100.0) / 100.0;
    }

    double median(std::vector<int> data) {
        std::sort(data.begin(), data.end());
        int n = static_cast<int>(data.size());

        if (n % 2 == 0) {
            int middle = n / 2;
            return std::round(((data[middle - 1] + data[middle]) / 2.0) * 100.0) / 100.0;
        } else {
            int middle = n / 2;
            return data[middle];
        }
    }

    std::vector<int> mode(const std::vector<int>& data) {
        std::unordered_map<int, long long> frequencyMap;
        for (int e : data) {
            frequencyMap[e]++;
        }

        long long maxCount = 0;
        for (const auto& pair : frequencyMap) {
            maxCount = std::max(maxCount, pair.second);
        }

        std::vector<int> result;
        for (const auto& pair : frequencyMap) {
            if (pair.second == maxCount) {
                result.push_back(pair.first);
            }
        }

        std::sort(result.begin(), result.end());
        return result;
    }
};