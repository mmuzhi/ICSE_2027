#include <vector>
#include <memory>
#include <optional>

class ArrangementCalculator {
private:
    std::vector<std::shared_ptr<void>> datas;

public:
    ArrangementCalculator(const std::vector<std::shared_ptr<void>>& datas) : datas(datas) {}

    static int count(int n) {
        return factorial(n);
    }

    static int count(int n, int m) {
        if (n == m) {
            return factorial(n);
        } else {
            return factorial(n) / factorial(n - m);
        }
    }

    static int countAll(int n) {
        int total = 0;
        for (int i = 1; i <= n; i++) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<std::shared_ptr<void>>> select(std::optional<int> m = std::nullopt) {
        int m_val;
        if (!m) {
            m_val = static_cast<int>(datas.size());
        } else {
            m_val = *m;
        }
        std::vector<std::vector<std::shared_ptr<void>>> result;
        std::vector<std::shared_ptr<void>> prefix;
        std::vector<std::shared_ptr<void>> remaining = datas;
        selectPermutations(prefix, remaining, m_val, result);
        return result;
    }

    std::vector<std::vector<std::shared_ptr<void>>> selectAll() {
        std::vector<std::vector<std::shared_ptr<void>>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); i++) {
            auto selections = select(i);
            result.insert(result.end(), selections.begin(), selections.end());
        }
        return result;
    }

private:
    void selectPermutations(std::vector<std::shared_ptr<void>> prefix, 
                            std::vector<std::shared_ptr<void>> remaining, 
                            int m, 
                            std::vector<std::vector<std::shared_ptr<void>>>& result) {
        if (static_cast<int>(prefix.size()) == m) {
            result.push_back(prefix);
            return;
        }
        for (size_t i = 0; i < remaining.size(); i++) {
            std::vector<std::shared_ptr<void>> newPrefix = prefix;
            newPrefix.push_back(remaining[i]);
            std::vector<std::shared_ptr<void>> newRemaining = remaining;
            newRemaining.erase(newRemaining.begin() + i);
            selectPermutations(newPrefix, newRemaining, m, result);
        }
    }

    static int factorial(int n) {
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
};