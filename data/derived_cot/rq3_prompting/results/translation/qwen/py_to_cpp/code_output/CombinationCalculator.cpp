#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

class CombinationCalculator {
public:
    CombinationCalculator(const std::vector<std::string>& datas) {
        datas_ = datas;
    }

    static int count(int n, int m) {
        if (m == 0 || n == m) {
            return 1;
        }

        unsigned long long result = 1;
        for (int i = 1; i <= m; ++i) {
            result = result * (n - i + 1) / i;
        }
        return static_cast<int>(result);
    }

    static int count_all(int n) {
        if (n < 0 || n > 63) {
            return 0;
        }
        if (n == 63) {
            return std::numeric_limits<int>::max();
        }
        return (1ULL << n) - 1;
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> current(m, "");
        _select(0, current, 0, result);
        return result;
    }

    std::vector<std::vector<std::string>> select_all() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= datas_.size(); ++i) {
            result.insert(result.end(), select(i).begin(), select(i).end());
        }
        return result;
    }

private:
    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex, std::vector<std::vector<std::string>>& result) {
        int resultLen = resultList.size();
        int resultCount = resultIndex + 1;

        if (resultCount > resultLen) {
            result.push_back(resultList);
            return;
        }

        for (int i = dataIndex; i < static_cast<int>(datas_.size()) + resultCount - resultLen; ++i) {
            resultList[resultIndex] = datas_[i];
            _select(i + 1, resultList, resultIndex + 1, result);
        }
    }

    std::vector<std::string> datas_;
};