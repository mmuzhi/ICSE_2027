#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>

class CombinationCalculator {
public:
    CombinationCalculator(const std::vector<std::string>& datas) {
        datas_ = datas;
    }

    static int count(int n, int m) {
        if (m < 0 || m > n) {
            return 0;
        }
        return std::factorial(n) / (std::factorial(n - m) * std::factorial(m));
    }

    static double count_all(int n) {
        if (n < 0 || n > 63) {
            return -1.0;
        }
        if (n == 63) {
            return std::numeric_limits<double>::infinity();
        }
        return std::pow(2.0, n) - 1.0;
    }

    std::vector<std::vector<std::string>> select(int m) {
        if (m < 1 || m > datas_.size()) {
            return {};
        }
        std::vector<std::vector<std::string>> result;
        _select(0, m, 0, result);
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
    void _select(int dataIndex, int m, int resultIndex, std::vector<std::vector<std::string>>& result) {
        if (resultIndex == m) {
            result.push_back(current_);
            return;
        }
        for (int i = dataIndex; i < datas_.size(); ++i) {
            current_.push_back(datas_[i]);
            _select(i + 1, m, resultIndex + 1, result);
            current_.pop_back();
        }
    }

    std::vector<std::string> current_;
    std::vector<std::string> datas_;
};