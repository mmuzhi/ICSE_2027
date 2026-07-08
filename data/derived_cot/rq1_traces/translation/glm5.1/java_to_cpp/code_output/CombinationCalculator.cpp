#include <vector>
#include <string>
#include <limits>
#include <iterator>

class CombinationCalculator {
private:
    std::vector<std::string> datas;

    static unsigned int factorial(int x) {
        unsigned int result = 1;
        for (int i = 1; i <= x; i++) {
            result *= static_cast<unsigned int>(i);
        }
        return result;
    }

protected:
    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex, std::vector<std::vector<std::string>>& result, int m) {
        if (resultIndex == m) {
            result.push_back(resultList);
            return;
        }

        for (int i = dataIndex; i <= static_cast<int>(datas.size()) - (m - resultIndex); i++) {
            // In the original Java, resultList.add(resultIndex, item) inserts at the end 
            // because resultIndex always equals the current size of resultList.
            resultList.push_back(datas[i]);
            _select(i + 1, resultList, resultIndex + 1, result, m);
            resultList.pop_back();
        }
    }

public:
    CombinationCalculator(std::vector<std::string> datas) : datas(std::move(datas)) {}

    static int count(int n, int m) {
        if (m == 0 || n == m) {
            return 1;
        }
        // Use unsigned int arithmetic to perfectly mimic Java's 32-bit two's complement overflow
        return static_cast<int>(factorial(n) / (factorial(n - m) * factorial(m)));
    }

    static double countAll(int n) {
        if (n < 0 || n > 63) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        if (n != 63) {
            // Java's `1 << n` on an int masks the right operand with 0x1F (n & 31).
            // We replicate this exact behavior to avoid C++ undefined shift/overflow issues.
            int shift = n & 0x1F;
            unsigned int shifted = 1U << shift;
            unsigned int val = shifted - 1;
            return static_cast<double>(static_cast<int>(val));
        }
        return std::numeric_limits<double>::infinity();
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> resultList;
        resultList.reserve(m); // Mimics `new ArrayList<>(m)` initial capacity
        _select(0, resultList, 0, result, m);
        return result;
    }

    std::vector<std::vector<std::string>> selectAll() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); i++) {
            auto partial = select(i);
            result.insert(result.end(), 
                          std::make_move_iterator(partial.begin()), 
                          std::make_move_iterator(partial.end()));
        }
        return result;
    }
};