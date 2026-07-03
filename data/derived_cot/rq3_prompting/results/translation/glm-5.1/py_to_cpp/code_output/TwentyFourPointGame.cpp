#include <vector>
#include <string>
#include <random>
#include <map>
#include <variant>
#include <cassert>
#include <cctype>
#include <stdexcept>

class TwentyFourPointGame {
public:
    std::vector<int> nums;

    TwentyFourPointGame() : nums() {}

    void _generate_cards() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 9);
        for (int i = 0; i < 4; i++) {
            nums.push_back(dist(gen));
        }
        assert(nums.size() == 4);
    }

    std::vector<int> get_my_cards() {
        nums.clear();
        _generate_cards();
        return nums;
    }

    std::variant<std::vector<int>, bool> answer(const std::string& expression) {
        if (expression == "pass") {
            return get_my_cards();
        }
        std::map<char, int> statistic;
        for (char c : expression) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                int digit = c - '0';
                bool in_nums = false;
                for (int n : nums) {
                    if (n == digit) {
                        in_nums = true;
                        break;
                    }
                }
                if (in_nums) {
                    statistic[c]++;
                }
            }
        }

        std::map<char, int> nums_used = statistic;

        for (int num : nums) {
            char key = '0' + num;
            if (nums_used.count(key) > 0 && nums_used[key] > 0) {
                nums_used[key] -= 1;
            } else {
                return false;
            }
        }

        bool all_zero = true;
        for (const auto& kv : nums_used) {
            if (kv.second != 0) {
                all_zero = false;
                break;
            }
        }

        if (all_zero) {
            return evaluate_expression(expression);
        } else {
            return false;
        }
    }

    bool evaluate_expression(const std::string& expression) {
        try {
            size_t pos = 0;
            double result = parse_expression(expression, pos);
            return result == 24.0;
        } catch (...) {
            return false;
        }
    }

private:
    double parse_expression(const std::string& expr, size_t& pos) {
        double result = parse_term(expr, pos);
        while (pos < expr.size()) {
            if (expr[pos] == '+') {
                pos++;
                result += parse_term(expr, pos);
            } else if (expr[pos] == '-') {
                pos++;
                result -= parse_term(expr, pos);
            } else {
                break;
            }
        }
        return result;
    }

    double parse_term(const std::string& expr, size_t& pos) {
        double result = parse_factor(expr, pos);
        while (pos < expr.size()) {
            if (expr[pos] == '*') {
                pos++;
                result *= parse_factor(expr, pos);
            } else if (expr[pos] == '/') {
                pos++;
                double divisor = parse_factor(expr, pos);
                if (divisor == 0.0) throw std::runtime_error("division by zero");
                result /= divisor;
            } else {
                break;
            }
        }
        return result;
    }

    double parse_factor(const std::string& expr, size_t& pos) {
        while (pos < expr.size() && expr[pos] == ' ') pos++;

        if (pos < expr.size() && expr[pos] == '(') {
            pos++;
            double result = parse_expression(expr, pos);
            while (pos < expr.size() && expr[pos] == ' ') pos++;
            if (pos < expr.size() && expr[pos] == ')') {
                pos++;
            }
            return result;
        }

        if (pos < expr.size() && expr[pos] == '-') {
            pos++;
            return -parse_factor(expr, pos);
        }

        if (pos < expr.size() && expr[pos] == '+') {
            pos++;
            return parse_factor(expr, pos);
        }

        double result = 0;
        bool has_digit = false;
        while (pos < expr.size() && std::isdigit(static_cast<unsigned char>(expr[pos]))) {
            result = result * 10 + (expr[pos] - '0');
            pos++;
            has_digit = true;
        }
        if (!has_digit) throw std::runtime_error("expected number");
        return result;
    }
};