#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <climits>
#include <cctype>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>
#include <new>
#include <type_traits>
#include <array>
#include <atomic>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <functional>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <typeinfo>
#include <utility>
#include <numeric>
#include <random>
#include <scoped_allocator>
#include <algorithm>

class ArrangementCalculator {
private:
    std::vector<int> datas;

    void generate(int m, std::vector<bool>& used, std::vector<int>& current, std::vector<std::vector<int>>& result) {
        if (static_cast<int>(current.size()) == m) {
            result.push_back(current);
            return;
        }
        for (int i = 0; i < static_cast<int>(datas.size()); i++) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(datas[i]);
                generate(m, used, current, result);
                current.pop_back();
                used[i] = false;
            }
        }
    }

public:
    ArrangementCalculator(const std::vector<int>& data) : datas(data) {}

    static long long factorial(int n) {
        if (n < 0) {
            return 0;
        }
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    static long long count(int n, int m = -1) {
        if (m == -1 || n == m) {
            return factorial(n);
        }
        if (m < 0 || m > n) {
            return 0;
        }
        return factorial(n) / factorial(n - m);
    }

    static long long count_all(int n) {
        long long total = 0;
        for (int i = 1; i <= n; i++) {
            total += count(n, i);
        }
        return total;
    }

    std::vector<std::vector<int>> select(int m = -1) {
        if (m == -1) {
            m = static_cast<int>(datas.size());
        }
        std::vector<std::vector<int>> result;
        std::vector<bool> used(datas.size(), false);
        std::vector<int> current;
        generate(m, used, current, result);
        return result;
    }

    std::vector<std::vector<int>> select_all() {
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= static_cast<int>(datas.size()); i++) {
            auto res = select(i);
            result.insert(result.end(), res.begin(), res.end());
        }
        return result;
    }
};