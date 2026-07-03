#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <cmath>

class DataStatistics {
public:
    double mean(const std::vector<int>& data) {
        double sum = std::accumulate(data.begin(), data.end(), 0);
        return std::round((sum / data.size()) * 100.0) / 100.0;
    }

    double median(const std::vector<int>& data) {
        std::vector<int> sortedData(data.begin(), data.end());
        std::sort(sortedData.begin(), sortedData.end());
        int n = sortedData.size();

        if (n % 2 == 0) {
            int middle = n / 2;
            return std::round(((sortedData[middle - 1] + sortedData[middle]) / 2.0) * 100.0) / 100.0;
        } else {
            int middle = n / 2;
            return sortedData[middle];
        }
    }

    std::vector<int> mode(const std::vector<int>& data) {
        std::unordered_map<int, long long> frequencyMap;
        for (int e : data) {
            frequencyMap[e]++;
        }

        long long maxCount = 0;
        for (const auto& pair : frequencyMap) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
            }
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