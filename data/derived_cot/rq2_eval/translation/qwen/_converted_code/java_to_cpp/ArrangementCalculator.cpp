#include <vector>

template <typename T>
class ArrangementCalculator {
private:
    std::vector<T> datas;

    void permutations_recursive(std::vector<T>& prefix, std::vector<T>& remaining, int m, std::vector<std::vector<T>>& result) {
        if (prefix.size() == m) {
            result.push_back(prefix);
            return;
        }
        for (int i = 0; i < remaining.size(); i++) {
            std::vector<T> newPrefix = prefix;
            newPrefix.push_back(remaining[i]);
            std::vector<T> newRemaining = remaining;
            newRemaining.erase(newRemaining.begin() + i);
            permutations_recursive(newPrefix, newRemaining, m, result);
        }
    }

public:
    ArrangementCalculator(std::vector<T> datas) : datas(datas) {}

    static int count(int n, int m) {
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

    std::vector<std::vector<T>> select(int m = -1) {
        if (m == -1) {
            m = datas.size();
        }
        std::vector<std::vector<T>> result;
        std::vector<T> prefix;
        std::vector<T> remaining = datas;
        permutations_recursive(prefix, remaining, m, result);
        return result;
    }

    std::vector<std::vector<T>> selectAll() {
        std::vector<std::vector<T>> result;
        for (int i = 1; i <= datas.size(); i++) {
            result.insert(result.end(), select(i).begin(), select(i).end());
        }
        return result;
    }

    static int factorial(int n) {
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
};