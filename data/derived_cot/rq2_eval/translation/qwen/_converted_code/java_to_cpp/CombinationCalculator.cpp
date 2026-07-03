#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iostream>

class CombinationCalculator {
private:
    std::vector<std::string> data_;

    void _select(int dataIndex, std::vector<std::string>& resultList, int resultIndex, 
                std::vector<std::vector<std::string>>& result, int m) {
        if (resultIndex == m) {
            result.push_back(resultList);
            return;
        }

        for (int i = dataIndex; i <= data_.size() - (m - resultIndex); ++i) {
            resultList.insert(resultList.begin() + resultIndex, data_[i]);
            _select(i + 1, resultList, resultIndex + 1, result, m);
            resultList.erase(resultList.begin() + resultIndex);
        }
    }

public:
    explicit CombinationCalculator(const std::vector<std::string>& data) : data_(data) {}

    static int count(int n, int m) {
        if (m == 0 || n == m) {
            return 1;
        }
        if (n < m) {
            return 0;
        }
        return factorial(n) / (factorial(n - m) * factorial(m));
    }

    private:
        static int factorial(int x) {
            int result = 1;
            for (int i = 1; i <= x; ++i) {
                result *= i;
            }
            return result;
        }

    public:
        static double count_all(int n) {
            if (n < 0 || n > 63) {
                return std::numeric_limits<double>::quiet_NaN();
            }
            if (n == 63) {
                return std::numeric_limits<double>::infinity();
            }
            return std::pow(2, n) - 1;
        }

    public:
        std::vector<std::vector<std::string>> select(int m) {
            if (m == 0) {
                throw std::invalid_argument("m must be between 1 and data size");
            }
            if (m > static_cast<int>(data_.size())) {
                return {};
            }

            std::vector<std::vector<std::string>> result;
            _select(0, std::vector<std::string>(), 0, result, m);
            return result;
        }

        std::vector<std::vector<std::string>> selectAll() {
            if (data_.empty()) {
                return {};
            }

            std::vector<std::vector<std::string>> allResults;
            for (int k = 1; k <= data_.size(); ++k) {
                allResults.insert(allResults.end(), select(k).begin(), select(k).end());
            }
            return allResults;
        }
};