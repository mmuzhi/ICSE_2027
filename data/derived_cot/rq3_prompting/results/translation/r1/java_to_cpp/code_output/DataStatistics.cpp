#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>
#include <stdexcept>

class DataStatistics {
public:
    double mean(const std::vector<int>& data) {
        if (data.empty()) {
            return 0.0;  // matches Java behavior: 0.0/0.0 → NaN → Math.round(NaN) = 0
        }
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return std::round((sum / data.size()) * 100.0) / 100.0;
    }

    double median(const std::vector<int>& data) {
        if (data.empty()) {
            throw std::out_of_range("Array index out of bounds");  // mimics Java ArrayIndexOutOfBoundsException
        }
        std::vector<int> sortedData = data;  // copy
        std::sort(sortedData.begin(), sortedData.end());
        size_t n = sortedData.size();
        if (n % 2 == 0) {
            size_t middle = n / 2;
            double avg = (sortedData[middle - 1] + sortedData[middle]) / 2.0;
            return std::round(avg * 100.0) / 100.0;
        } else {
            size_t middle = n / 2;
            return static_cast<double>(sortedData[middle]);
        }
    }

    std::vector<int> mode(const std::vector<int>& data) {
        std::unordered_map<int, size_t> freq;
        for (int x : data) {
            ++freq[x];
        }
        if (freq.empty()) {
            throw std::runtime_error("NoSuchElementException");  // mimics Java's NoSuchElementException
        }
        size_t maxCount = 0;
        for (const auto& p : freq) {
            if (p.second > maxCount) {
                maxCount = p.second;
            }
        }
        std::vector<int> result;
        for (const auto& p : freq) {
            if (p.second == maxCount) {
                result.push_back(p.first);
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }
};