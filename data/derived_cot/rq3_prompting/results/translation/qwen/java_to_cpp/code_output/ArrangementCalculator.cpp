#include <vector>
#include <optional>
#include <functional>

namespace org::example {

    template <typename T>
    class ArrangementCalculator {
    private:
        std::vector<T> datas;

    public:
        explicit ArrangementCalculator(const std::vector<T>& datas) : datas(datas) {}

        std::vector<std::vector<T>> select(std::optional<int> m = std::nullopt) {
            int m_val = m.value_or(static_cast<int>(datas.size()));
            std::vector<std::vector<T>> result;
            selectPermutations(std::vector<T>(), datas, m_val, result);
            return result;
        }

        std::vector<std::vector<T>> selectAll() {
            std::vector<std::vector<T>> result;
            for (int i = 1; i <= datas.size(); ++i) {
                result.insert(result.end(), select(i).begin(), select(i).end());
            }
            return result;
        }

    private:
        void selectPermutations(std::vector<T> prefix, const std::vector<T>& remaining, int m, std::vector<std::vector<T>>& result) {
            if (prefix.size() == m) {
                result.push_back(prefix);
                return;
            }
            for (int i = 0; i < remaining.size(); ++i) {
                std::vector<T> newPrefix = prefix;
                newPrefix.push_back(remaining[i]);
                std::vector<T> newRemaining = remaining;
                newRemaining.erase(newRemaining.begin() + i);
                selectPermutations(newPrefix, newRemaining, m, result);
            }
        }
    };

    namespace {
        int factorial(int n) {
            if (n < 0) return 1;
            int result = 1;
            for (int i = 2; i <= n; ++i) {
                result *= i;
            }
            return result;
        }

        int count(int n, std::optional<int> m = std::nullopt) {
            if (!m.has_value() || n == m.value()) {
                return factorial(n);
            } else {
                return factorial(n) / factorial(n - m.value());
            }
        }

        int countAll(int n) {
            int total = 0;
            for (int i = 1; i <= n; ++i) {
                total += count(n, i);
            }
            return total;
        }
    }

} // namespace org::example