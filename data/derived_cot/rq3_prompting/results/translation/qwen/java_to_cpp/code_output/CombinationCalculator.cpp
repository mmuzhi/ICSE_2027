#include <vector>
#include <string>
#include <limits>

class CombinationCalculator {
private:
    std::vector<std::string> datas;

public:
    CombinationCalculator(const std::vector<std::string>& datas) : datas(datas) {}

    static int count(int n, int m) {
        if (m == 0 || n == m) {
            return 1;
        }
        return factorial(n) / (factorial(n - m) * factorial(m));
    }

private:
    static int factorial(int x) {
        int result = 1;
        for (int i = 1; i <= x; i++) {
            result *= i;
        }
        return result;
    }

public:
    static double countAll(int n) {
        if (n < 0 || n > 63) {
            return std::numeric_limits<double>::NaN();
        }
        if (n == 63) {
            return std::numeric_limits<double>::infinity();
        }
        return (1LL << n) - 1;
    }

public:
    std::vector<std::vector<std::string>> select(int m) {
        std::vector<std::vector<std::string>> result;
        _select(0, std::vector<std::string>(), 0, result, m);
        return result;
    }

    std::vector<std::vector<std::string>> selectAll() {
        std::vector<std::vector<std::string>> result;
        for (int i = 1; i <= datas.size(); i++) {
            result.insert(result.end(), select(i).begin(), select(i).end());
        }
        return result;
    }

private:
    void _select(int currentIndex, std::vector<std::string>& currentCombination, int currentSize, std::vector<std::vector<std::string>>& result, int m) {
        if (currentSize == m) {
            result.push_back(currentCombination);
            return;
        }

        int maxIndex = datas.size() - (m - currentSize);
        for (int i = currentIndex; i <= maxIndex; i++) {
            currentCombination.push_back(datas[i]);
            _select(i + 1, currentCombination, currentSize + 1, result, m);
            currentCombination.pop_back();
        }
    }
};