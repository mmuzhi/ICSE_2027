#include <vector>
#include <string>
#include <limits>
#include <stdexcept>

class CombinationCalculator {
private:
    std::vector<std::string> datas;

    static int factorial(int x) {
        int result = 1;
        for (int i = 1; i <= x; ++i) {
            result *= i;
        }
        return result;
    }

    void _select(int dataIndex, std::vector<std::string>& resultList,
                 int resultIndex, std::vector<std::vector<std::string>>& result,
                 int m) {
        if (resultIndex == m) {
            result.push_back(std::vector<std::string>(resultList));
            return;
        }

        // Note: the loop condition matches Java exactly, including potential out-of-bounds access
        // when m == 0 (which causes an exception via .at()).
        for (int i = dataIndex; i <= static_cast<int>(datas.size()) - (m - resultIndex); ++i) {
            resultList[resultIndex] = datas.at(i);
            _select(i + 1, resultList, resultIndex + 1, result, m);
            // No need to remove because we overwrite on next iteration or after recursion returns.
        }
    }

public:
    CombinationCalculator(const std::vector<std::string>& datas) : datas(datas) {}

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
        // Replicate Java's int semantics: shift uses only lower 5 bits of n.
        unsigned int val = (1U << (n & 0x1F)) - 1U;
        return static_cast<double>(val);
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> resultList(m);
        _select(0, resultList, 0, result, m);
        return result;
    }

    std::vector<std::vector<std::string>> selectAll() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            std::vector<std::vector<std::string>> sub = select(i);
            result.insert(result.end(), sub.begin(), sub.end());
        }
        return result;
    }
};