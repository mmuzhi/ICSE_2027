#include <vector>
#include <any>
#include <optional>
#include <stdexcept>

class ArrangementCalculator {
private:
    std::vector<std::any> datas;

    void selectPermutations(std::vector<std::any> prefix,
                            std::vector<std::any> remaining,
                            int m,
                            std::vector<std::vector<std::any>>& result) {
        if (static_cast<int>(prefix.size()) == m) {
            result.push_back(prefix);
            return;
        }
        for (std::size_t i = 0; i < remaining.size(); ++i) {
            std::vector<std::any> newPrefix = prefix;
            newPrefix.push_back(remaining[i]);
            std::vector<std::any> newRemaining;
            newRemaining.reserve(remaining.size() - 1);
            for (std::size_t j = 0; j < remaining.size(); ++j) {
                if (j != i) {
                    newRemaining.push_back(remaining[j]);
                }
            }
            selectPermutations(newPrefix, newRemaining, m, result);
        }
    }

public:
    ArrangementCalculator(const std::vector<std::any>& datas) : datas(datas) {}

    static int factorial(int n) {
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    static int count(int n, std::optional<int> m = std::nullopt) {
        if (!m.has_value() || n == m.value()) {
            return factorial(n);
        } else {
            return factorial(n) / factorial(n - m.value());
        }
    }

    static int countAll(int n) {
        int total = 0;
        for (int i = 1; i <= n; ++i) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<std::any>> select(std::optional<int> m = std::nullopt) {
        if (!m.has_value()) {
            m = static_cast<int>(datas.size());
        }
        std::vector<std::vector<std::any>> result;
        selectPermutations({}, datas, m.value(), result);
        return result;
    }

    std::vector<std::vector<std::any>> selectAll() {
        std::vector<std::vector<std::any>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            auto partial = select(i);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }
};