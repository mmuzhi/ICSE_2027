#include <vector>
#include <algorithm>
#include <functional>

class ArrangementCalculator {
private:
    std::vector<int> datas;

public:
    ArrangementCalculator(const std::vector<int>& datas) : datas(datas) {}

    static int factorial(int n) {
        if (n < 0) return 0;
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    static int count(int n, int m = -1) {
        if (m == -1 || n == m) {
            return factorial(n);
        } else {
            return factorial(n) / factorial(n - m);
        }
    }

    static int count_all(int n) {
        int total = 0;
        for (int i = 1; i <= n; i++) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<int>> select(int m = -1) {
        int len = datas.size();
        if (m == -1) {
            m = len;
        }
        if (m > len) {
            return {};
        }
        std::vector<bool> used(len, false);
        std::vector<int> current;
        std::vector<std::vector<int>> result;
        std::function<void(int)> generate = [&](int remaining) {
            if (remaining == 0) {
                result.push_back(current);
                return;
            }
            for (int i = 0; i < len; i++) {
                if (!used[i]) {
                    used[i] = true;
                    current.push_back(datas[i]);
                    generate(remaining - 1);
                    current.pop_back();
                    used[i] = false;
                }
            }
        };
        generate(m);
        return result;
    }

    std::vector<std::vector<int>> select_all() {
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= datas.size(); i++) {
            result.insert(result.end(), select(i).begin(), select(i).end());
        }
        return result;
    }
};