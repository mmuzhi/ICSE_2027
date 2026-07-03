#include <vector>
#include <cstddef>

class ArrangementCalculator {
private:
    std::vector<int> datas;

    // Helper to generate all permutations of length r from datas.
    void generatePermutations(std::vector<int>& current,
                              std::vector<bool>& used,
                              int r,
                              std::vector<std::vector<int>>& result) const {
        if (static_cast<int>(current.size()) == r) {
            result.push_back(current);
            return;
        }
        for (std::size_t i = 0; i < datas.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(datas[i]);
                generatePermutations(current, used, r, result);
                current.pop_back();
                used[i] = false;
            }
        }
    }

public:
    // Constructor
    ArrangementCalculator(const std::vector<int>& datas) : datas(datas) {}

    // Static: factorial
    static long long factorial(int n) {
        if (n <= 1) return 1;
        long long res = 1;
        for (int i = 2; i <= n; ++i)
            res *= i;
        return res;
    }

    // Static: count of permutations P(n, m)
    // m == -1 means "m not provided" (equivalent to Python's None)
    static long long count(int n, int m = -1) {
        if (m == -1 || n == m)
            return factorial(n);
        else
            return factorial(n) / factorial(n - m);
    }

    // Static: total number of arrangements of length 1..n
    static long long count_all(int n) {
        long long total = 0;
        for (int i = 1; i <= n; ++i)
            total += count(n, i);
        return total;
    }

    // Instance: generate all permutations of size m from stored datas.
    // m == -1 means use all datas (default).
    std::vector<std::vector<int>> select(int m = -1) {
        if (m == -1)
            m = static_cast<int>(datas.size());
        if (m < 0 || m > static_cast<int>(datas.size()))
            return {};
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        std::vector<bool> used(datas.size(), false);
        generatePermutations(current, used, m, result);
        return result;
    }

    // Instance: generate all permutations of length 1..size
    std::vector<std::vector<int>> select_all() {
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); ++i) {
            auto sub = select(i);
            result.insert(result.end(), sub.begin(), sub.end());
        }
        return result;
    }
};