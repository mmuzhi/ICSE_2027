#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <stdexcept>

class DataStatistics {
public:
    double mean(const std::vector<int>& data) {
        if (data.empty()) {
            return 0.0;
        }
        double sum = 0.0;
        for (int num : data) {
            sum += num;
        }
        double avg = sum / static_cast<double>(data.size());
        double temp = avg * 100.0;
        temp = std::round(temp);
        return temp / 100.0;
    }

    double median(std::vector<int> data) {
        if (data.empty()) {
            throw std::out_of_range("Array index out of bounds");
        }
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 0) {
            size_t mid = n / 2;
            double midValue = (static_cast<double>(data[mid-1]) + data[mid]) / 2.0;
            double temp = midValue * 100.0;
            temp = std::round(temp);
            return temp / 100.0;
        } else {
            return static_cast<double>(data[n/2]);
        }
    }

    std::vector<int> mode(const std::vector<int>& data) {
        if (data.empty()) {
            throw std::runtime_error("No such element");
        }
        std::map<int, long> frequencyMap;
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