#include <vector>
#include <string>
#include <cmath>

class CombinationCalculator {
public:
    std::vector<std::string> datas;

    CombinationCalculator(const std::vector<std::string>& datas) : datas(datas) {}

    static long long count(int n, int m) {
        if (m == 0 || n == m) return 1;
        if (m > n - m) m = n - m;
        long long result = 1;
        for (int i = 0; i < m; i++) {
            result = result * (n - i) / (i + 1);
        }
        return result;
    }

    static double count_all(int n) {
        if (n < 0 || n > 63) return 0;
        if (n == 63) return INFINITY;
        return (1LL << n) - 1;
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> resultList(m);
        _select(0, resultList, 0, result);
        return result;
    }

    std::vector<std::vector<std::string>> select_all() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); i++) {
            auto sub = select(i);
            result.insert(result.end(), sub.begin(), sub.end());
        }
        return result;
    }

    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex, std::vector<std::vector<std::string>>& result) {
        int resultLen = static_cast<int>(resultList.size());
        int resultCount = resultIndex + 1;
        if (resultCount > resultLen) {
            result.push_back(resultList);
            return;
        }
        int loopEnd = static_cast<int>(datas.size()) + resultCount - resultLen;
        for (int i = dataIndex; i < loopEnd; i++) {
            resultList[resultIndex] = datas[i];
            _select(i + 1, resultList, resultIndex + 1, result);
        }
    }
};