#include <vector>
#include <optional>

class ArrangementCalculator {
private:
    std::vector<int> datas;

    // Helper method to generate permutations recursively, matching itertools.permutations behavior
    void generate_permutations(int k, std::vector<bool>& used, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        if (static_cast<int>(current.size()) == k) {
            result.push_back(current);
            return;
        }
        for (size_t i = 0; i < datas.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(datas[i]);
                generate_permutations(k, used, current, result);
                current.pop_back();
                used[i] = false;
            }
        }
    }

public:
    ArrangementCalculator(std::vector<int> datas) : datas(std::move(datas)) {}

    static long long count(int n, std::optional<int> m = std::nullopt) {
        if (!m.has_value() || n == m.value()) {
            return factorial(n);
        } else {
            return factorial(n) / factorial(n - m.value());
        }
    }

    static long long count_all(int n) {
        long long total = 0;
        for (int i = 1; i <= n; ++i) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<int>> select(std::optional<int> m = std::nullopt) {
        int k = m.value_or(static_cast<int>(datas.size()));
        std::vector<std::vector<int>> result;
        std::vector<bool> used(datas.size(), false);
        std::vector<int> current;
        generate_permutations(k, used, current, result);
        return result;
    }

    std::vector<std::vector<int>> select_all() {
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            std::vector<std::vector<int>> partial = select(i);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }

    static long long factorial(int n) {
        long long result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
};