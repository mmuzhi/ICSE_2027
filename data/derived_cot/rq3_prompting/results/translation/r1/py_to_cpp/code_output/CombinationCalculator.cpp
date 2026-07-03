#include <vector>
#include <string>
#include <cmath>
#include <cstdint>
#include <stdexcept>

class CombinationCalculator {
private:
    std::vector<std::string> datas;

    // Recursive helper for combination generation
    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex,
                 std::vector<std::vector<std::string>>& result) {
        int resultLen = static_cast<int>(resultList.size());
        int resultCount = resultIndex + 1;
        if (resultCount > resultLen) {
            result.push_back(resultList); // copy is made
            return;
        }

        int limit = static_cast<int>(datas.size()) + resultCount - resultLen;
        for (int i = dataIndex; i < limit; ++i) {
            resultList[resultIndex] = datas[i];
            _select(i + 1, resultList, resultIndex + 1, result);
        }
    }

public:
    explicit CombinationCalculator(const std::vector<std::string>& datas) : datas(datas) {}

    static long long count(int n, int m) {
        if (m == 0 || n == m) return 1;
        // Compute factorial iteratively to avoid double factorial function
        long long numerator = 1;
        int smaller = (m < n - m) ? m : n - m;
        for (int i = 0; i < smaller; ++i) {
            numerator *= (n - i);
        }
        long long denominator = 1;
        for (int i = 2; i <= smaller; ++i) {
            denominator *= i;
        }
        return numerator / denominator;
    }

    static double count_all(int n) {
        if (n < 0 || n > 63) {
            return 0.0; // equivalent to Python's False (which is 0)
        }
        if (n == 63) {
            return INFINITY; // Python: float("inf")
        }
        // (1 << n) - 1 as double for large numbers, but n <= 62 fits in 64-bit
        uint64_t val = (static_cast<uint64_t>(1) << n) - 1;
        return static_cast<double>(val);
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> resultList(m);
        _select(0, resultList, 0, result);
        return result;
    }

    std::vector<std::vector<std::string>> select_all() {
        std::vector<std::vector<std::string>> result;
        int n = static_cast<int>(datas.size());
        for (int i = 1; i <= n; ++i) {
            auto part = select(i);
            result.insert(result.end(), part.begin(), part.end());
        }
        return result;
    }
};