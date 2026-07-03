#include <vector>
#include <functional>

class ArrangementCalculator {
public:
    ArrangementCalculator(const std::vector<int>& datas) : datas(datas) {}

    static int factorial(int n) {
        if (n < 0) {
            return 0;
        }
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    static int count(int n, int m = -1) {
        if (m == -1) {
            m = n;
        }
        if (m > n) {
            return 0;
        }
        if (m == n) {
            return factorial(n);
        }
        return factorial(n) / factorial(n - m);
    }

    static int count_all(int n) {
        int total = 0;
        for (int i = 1; i <= n; ++i) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<int>> select(int m = -1) {
        if (m == -1) {
            m = datas.size();
        }
        if (m > static_cast<int>(datas.size())) {
            return {};
        }
        return generate_permutations(datas, m);
    }

    std::vector<std::vector<int>> select_all() {
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= datas.size(); ++i) {
            result.insert(result.end(), generate_permutations(datas, i).begin(), generate_permutations(datas, i).end());
        }
        return result;
    }

private:
    std::vector<int> datas;

    std::vector<std::vector<int>> generate_permutations(const std::vector<int>& data, int m) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        int n = data.size();
        std::vector<bool> used(n, false);

        std::function<void(int)> dfs = [&](int depth) {
            if (depth == m) {
                result.push_back(current);
                return;
            }
            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    used[i] = true;
                    current.push_back(data[i]);
                    dfs(depth + 1);
                    current.pop_back();
                    used[i] = false;
                }
            }
        };

        dfs(0);
        return result;
    }
};