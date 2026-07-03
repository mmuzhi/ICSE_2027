#include <vector>
#include <string>
#include <map>
#include <random>
#include <cassert>
#include <cctype>
#include <variant>
#include <stdexcept>

class TwentyFourPointGame {
private:
    std::vector<int> nums;
    std::mt19937 gen{std::random_device{}()};

    void _generate_cards() {
        std::uniform_int_distribution<> distrib(1, 9);
        for (int i = 0; i < 4; ++i) {
            nums.push_back(distrib(gen));
        }
        assert(nums.size() == 4);
    }

    class Parser {
    public:
        Parser(const std::string& expr) : expr_(expr), pos_(0) {}

        double parse() {
            double result = parseExpression();
            skipSpaces();
            if (pos_ < expr_.size()) {
                throw std::runtime_error("Unexpected character");
            }
            return result;
        }

    private:
        std::string expr_;
        size_t pos_;

        void skipSpaces() {
            while (pos_ < expr_.size() && std::isspace(expr_[pos_])) {
                pos_++;
            }
        }

        char peek() {
            skipSpaces();
            if (pos_ < expr_.size()) {
                return expr_[pos_];
            }
            return '\0';
        }

        char consume() {
            skipSpaces();
            if (pos_ < expr_.size()) {
                return expr_[pos_++];
            }
            return '\0';
        }

        double parseExpression() {
            double result = parseTerm();
            while (true) {
                char op = peek();
                if (op == '+' || op == '-') {
                    consume();
                    double term = parseTerm();
                    if (op == '+') {
                        result += term;
                    } else {
                        result -= term;
                    }
                } else {
                    break;
                }
            }
            return result;
        }

        double parseTerm() {
            double result = parseFactor();
            while (true) {
                char op = peek();
                if (op == '*' || op == '/') {
                    consume();
                    double factor = parseFactor();
                    if (op == '*') {
                        result *= factor;
                    } else {
                        if (factor == 0) {
                            throw std::runtime_error("Division by zero");
                        }
                        result /= factor;
                    }
                } else {
                    break;
                }
            }
            return result;
        }

        double parseFactor() {
            char c = peek();
            if (c == '(') {
                consume();
                double result = parseExpression();
                if (peek() == ')') {
                    consume();
                } else {
                    throw std::runtime_error("Missing closing parenthesis");
                }
                return result;
            } else if (c == '-' || c == '+') {
                consume();
                double factor = parseFactor();
                return c == '-' ? -factor : factor;
            } else if (std::isdigit(c)) {
                return parseNumber();
            } else {
                throw std::runtime_error("Unexpected character in factor");
            }
        }

        double parseNumber() {
            skipSpaces();
            size_t start_pos = pos_;
            while (pos_ < expr_.size() && std::isdigit(expr_[pos_])) {
                pos_++;
            }
            if (pos_ == start_pos) {
                throw std::runtime_error("Expected number");
            }
            return std::stod(expr_.substr(start_pos, pos_ - start_pos));
        }
    };

public:
    TwentyFourPointGame() = default;

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
            if (std::isdigit(c)) {
                int num = c - '0';
                for (int n : nums) {
                    if (n == num) {
                        statistic[c]++;
                        break;
                    }
                }
            }
        }

        std::map<char, int> nums_used = statistic;

        for (int num : nums) {
            char c = '0' + num;
            auto it = nums_used.find(c);
            if (it != nums_used.end() && it->second > 0) {
                it->second--;
            } else {
                return false;
            }
        }

        bool all_zero = true;
        for (const auto& pair : nums_used) {
            if (pair.second != 0) {
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
            Parser parser(expression);
            double result = parser.parse();
            return result == 24.0;
        } catch (...) {
            return false;
        }
    }
};