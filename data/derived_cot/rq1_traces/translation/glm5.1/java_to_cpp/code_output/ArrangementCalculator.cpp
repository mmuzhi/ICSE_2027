#include <vector>
#include <any>
#include <optional>

class ArrangementCalculator {
private:
    std::vector<std::any> datas;

    void selectPermutations(const std::vector<std::any>& prefix, const std::vector<std::any>& remaining, int m, std::vector<std::vector<std::any>>& result) {
        if (prefix.size() == static_cast<size_t>(m)) {
            result.push_back(prefix); // push_back copies the prefix, matching Java's new ArrayList<>(prefix)
            return;
        }
        for (size_t i = 0; i < remaining.size(); i++) {
            std::vector<std::any> newPrefix = prefix;
            newPrefix.push_back(remaining[i]);
            
            std::vector<std::any> newRemaining = remaining;
            newRemaining.erase(newRemaining.begin() + i); // equivalent to Java's remove(i)
            
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

public:
    ArrangementCalculator(std::vector<std::any> datas) : datas(std::move(datas)) {}

    static int count(int n, std::optional<int> m) {
        if (!m.has_value() || n == m.value()) {
            return factorial(n);
        } else {
            return factorial(n) / factorial(n - m.value());
        }
    }

    static int countAll(int n) {
        int total = 0;
        for (int i = 1; i <= n; i++) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<std::any>> select(std::optional<int> m) {
        if (!m.has_value()) {
            m = static_cast<int>(datas.size());
        }
        std::vector<std::vector<std::any>> result;
        selectPermutations({}, datas, m.value(), result);
        return result;
    }

    std::vector<std::vector<std::any>> selectAll() {
        std::vector<std::vector<std::any>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); i++) {
            auto partial = select(i);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }
};