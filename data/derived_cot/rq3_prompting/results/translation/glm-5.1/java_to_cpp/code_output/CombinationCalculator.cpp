#pragma once
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <cstdint>

class CombinationCalculator {
private:
    std::vector<std::string> datas;

    static int factorial(int x) {
        int result = 1;
        for (int i = 1; i <= x; i++) {
            result *= i;
        }
        return result;
    }

protected:
    virtual void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex,
                          std::vector<std::vector<std::string>>& result, int m) {
        if (resultIndex == m) {
            result.push_back(resultList);
            return;
        }
        for (int i = dataIndex; i <= static_cast<int>(datas.size()) - (m - resultIndex); i++) {
            resultList.insert(resultList.begin() + resultIndex, datas[i]);
            _select(i + 1, resultList, resultIndex + 1, result, m);
            resultList.erase(resultList.begin() + resultIndex);
        }
    }

public:
    CombinationCalculator(const std::vector<std::string>& datas) : datas(datas) {}

    virtual ~CombinationCalculator() = default;

    static int count(int n, int m) {
        if (m == 0 || n == m) {
            return 1;
        }
        return factorial(n) / (factorial(n - m) * factorial(m));
    }

    static double countAll(int n) {
        if (n < 0 || n > 63) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        if (n == 63) {
            return std::numeric_limits<double>::infinity();
        }
        // Replicate Java int shift: (1 << n) - 1, where << masks n & 0x1f on 32-bit int
        uint32_t u_shifted = 1u << static_cast<unsigned>(n & 0x1f);
        uint32_t u_val = u_shifted - 1u;
        return static_cast<double>(static_cast<int32_t>(u_val));
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> resultList;
        _select(0, resultList, 0, result, m);
        return result;
    }

    std::vector<std::vector<std::string>> selectAll() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); i++) {
            std::vector<std::vector<std::string>> sub = select(i);
            result.insert(result.end(), sub.begin(), sub.end());
        }
        return result;
    }
};