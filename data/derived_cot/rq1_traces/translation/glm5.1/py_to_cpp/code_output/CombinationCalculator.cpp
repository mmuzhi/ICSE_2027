#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <utility>

class CombinationCalculator {
public:
    std::vector<std::string> datas;

    // Constructor to initialize the calculator with a list of data.
    explicit CombinationCalculator(std::vector<std::string> datas) : datas(std::move(datas)) {}

    // Calculate the number of combinations for a specific count.
    static long long count(int n, int m) {
        if (n < 0 || m < 0 || n < m) {
            throw std::invalid_argument("Invalid arguments for count");
        }
        if (m == 0 || n == m) {
            return 1;
        }
        if (m > n - m) {
            m = n - m;
        }
        long long res = 1;
        for (int i = 0; i < m; ++i) {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }

    // Calculate the number of all possible combinations.
    // Returns a double to accommodate infinity for n == 63, matching Python's float("inf").
    // Returns 0.0 for invalid n, matching Python's False (which evaluates to 0).
    static double count_all(int n) {
        if (n < 0 || n > 63) {
            return 0.0;
        }
        if (n == 63) {
            return std::numeric_limits<double>::infinity();
        }
        return static_cast<double>((1ULL << n) - 1);
    }

    // Generate combinations with a specified number of elements.
    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> resultList;
        if (m > 0) {
            resultList.resize(m);
        }
        _select(0, resultList, 0, result);
        return result;
    }

    // Generate all possible combinations of selecting elements from the given data list.
    std::vector<std::vector<std::string>> select_all() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            auto sub = select(i);
            result.insert(result.end(), sub.begin(), sub.end());
        }
        return result;
    }

    // Generate combinations with a specified number of elements by recursion.
    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex, std::vector<std::vector<std::string>>& result) {
        int resultLen = static_cast<int>(resultList.size());
        int resultCount = resultIndex + 1;
        
        if (resultCount > resultLen) {
            result.push_back(resultList);
            return;
        }

        for (int i = dataIndex; i < static_cast<int>(datas.size()) + resultCount - resultLen; ++i) {
            resultList[resultIndex] = datas[i];
            _select(i + 1, resultList, resultIndex + 1, result);
        }
    }
};