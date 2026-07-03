#include <vector>
#include <optional>

class ArrangementCalculator {
public:
    std::vector<int> datas;

    ArrangementCalculator(std::vector<int> datas) : datas(std::move(datas)) {}

    static long long factorial(int n) {
        long long result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

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
        int k = m.value_or(datas.size());
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        std::vector<bool> used(datas.size(), false);
        generate_permutations(k, result, current, used);
        return result;
    }

    std::vector<std::vector<int>> select_all() {
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            auto partial = select(i);
            result.insert(result.end(), partial.begin(), partial.end());
        }
        return result;
    }

private:
    void generate_permutations(int m, std::vector<std::vector<int>>& result, std::vector<int>& current, std::vector<bool>& used) {
        if (static_cast<int>(current.size()) == m) {
            result.push_back(current);
            return;
        }
        for (size_t i = 0; i < datas.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(datas[i]);
                generate_permutations(m, result, current, used);
                current.pop_back();
                used[i] = false;
            }
        }
    }
};