#include <vector>
#include <string>
#include <limits>

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

    void _select(int dataIndex, std::vector<std::string>& current, int resultIndex, std::vector<std::vector<std::string>>& result, int m) {
        if (resultIndex == m) {
            result.push_back(current);
            return;
        }

        for (int i = dataIndex; i <= static_cast<int>(datas.size()) - (m - resultIndex); ++i) {
            current.push_back(datas[i]);
            _select(i + 1, current, resultIndex + 1, result, m);
            current.pop_back();
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
        return static_cast<double>((1LL << n) - 1);
    }

    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> current;
        current.reserve(m);
        _select(0, current, 0, result, m);
        return result;
    }

    std::vector<std::vector<std::string>> selectAll() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            auto subsets = select(i);
            result.insert(result.end(), subsets.begin(), subsets.end());
        }
        return result;
    }
};