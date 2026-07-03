#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

class DataStatistics {
public:
    double mean(const std::vector<int>& data) {
        if (data.empty()) {
            throw std::domain_error("DataStatistics::mean: empty array");
        }
        double sum = 0.0;
        for (int num : data) {
            sum += num;
        }
        double average = sum / data.size();
        long rounded = static_cast<long>(std::round(average * 100.0));
        return static_cast<double>(rounded) / 100.0;
    }

    double median(std::vector<int> data) {
        if (data.empty()) {
            throw std::domain_error("DataStatistics::median: empty array");
        }
        std::sort(data.begin(), data.end());
        int n = data.size();

        if (n % 2 == 0) {
            int middle = n / 2;
            double average = (static_cast<double>(data[middle - 1]) + data[middle]) / 2.0;
            long rounded = static_cast<long>(std::round(average * 100.0));
            return static_cast<double>(rounded) / 100.0;
        } else {
            int middle = n / 2;
            return data[middle];
        }
    }

    std::vector<int> mode(std::vector<int> data) {
        if (data.empty()) {
            return {};
        }

        std::unordered_map<int, long> frequencyMap;
        for (int num : data) {
            frequencyMap[num]++;
        }

        long maxCount = 0;
        for (const auto& pair : frequencyMap) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
            }
        }

        std::vector<int> modes;
        for (const auto& pair : frequencyMap) {
            if (pair.second == maxCount) {
                modes.push_back(pair.first);
            }
        }

        std::sort(modes.begin(), modes.end());
        return modes;
    }
};