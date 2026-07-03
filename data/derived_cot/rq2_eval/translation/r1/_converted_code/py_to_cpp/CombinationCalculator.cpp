#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <iostream>

class CombinationCalculator {
private:
    std::vector<std::string> datas;

    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex, std::vector<std::vector<std::string>>& result) {
        int resultLen = resultList.size();
        int resultCount = resultIndex + 1;
        if (resultCount > resultLen) {
            result.push_back(resultList);
            return;
        }

        int n = datas.size();
        int end = n + resultCount - resultLen;
        for (int i = dataIndex; i < end; i++) {
            resultList[resultIndex] = datas[i];
            _select(i + 1, resultList, resultIndex + 1, result);
        }
    }

public:
    CombinationCalculator(const std::vector<std::string>& datas) : datas(datas) {}

    static long long count(int n, int m) {
        if (m < 0 || m > n) {
            throw std::invalid_argument("m must be between 0 and n");
        }
        if (n > 63) {
            throw std::invalid_argument("n must be <= 63");
        }
        if (m == 0 || m == n) {
            return 1;
        }
        if (m > n - m) {
            m = n - m;
        }
        long long res = 1;
        for (int i = 0; i < m; i++) {
            res = res * (n - i) / (i + 1);
        }
        return res;
    }

    static double count_all(int n) {
        if (n < 0 || n > 63) {
            return 0.0;
        }
        if (n == 63) {
            return std::numeric_limits<double>::infinity();
        }
        return static_cast<double>((1LL << n) - 1);
    }

    std::vector<std::vector<std::string>> select(int m) {
        if (m < 0) {
            throw std::invalid_argument("m must be non-negative");
        }
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> temp(m);
        _select(0, temp, 0, result);
        return result;
    }

    std::vector<std::vector<std::string>> select_all() {
        std::vector<std::vector<std::string>> result;
        int n = datas.size();
        for (int i = 1; i <= n; i++) {
            auto comb = select(i);
            result.insert(result.end(), comb.begin(), comb.end());
        }
        return result;
    }
};