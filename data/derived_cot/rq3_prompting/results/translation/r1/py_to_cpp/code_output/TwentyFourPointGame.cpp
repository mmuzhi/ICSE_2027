#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <stdexcept>
#include <random>
#include <sstream>
#include <cmath>

class TwentyFourPointGame {
private:
    std::vector<int> nums;

    void _generate_cards() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dist(1, 9);
        for (int i = 0; i < 4; ++i) {
            nums.push_back(dist(gen));
        }
    }

    // Recursive descent parser for arithmetic expressions (supports +, -, *, /, parentheses)
    struct Parser {
        std::string input;
        size_t pos;

        Parser(const std::string& s) : input(s), pos(0) {}

        double parse() {
            double result = parseExpr();
            if (pos != input.size()) {
                throw std::runtime_error("Unexpected characters");
            }
            return result;
        }

    private:
        double parseExpr() {
            double left = parseTerm();
            while (pos < input.size()) {
                char op = input[pos];
                if (op == '+' || op == '-') {
                    pos++;
                    double right = parseTerm();
                    if (op == '+') left += right;
                    else left -= right;
                } else {
                    break;
                }
            }
            return left;
        }

        double parseTerm() {
            double left = parseFactor();
            while (pos < input.size()) {
                char op = input[pos];
                if (op == '*' || op == '/') {
                    pos++;
                    double right = parseFactor();
                    if (op == '*') left *= right;
                    else {
                        if (std::fabs(right) < 1e-12) {
                            throw std::runtime_error("Division by zero");
                        }
                        left /= right;
                    }
                } else {
                    break;
                }
            }
            return left;
        }

        double parseFactor() {
            if (pos >= input.size()) {
                throw std::runtime_error("Unexpected end of expression");
            }
            if (input[pos] == '(') {
                pos++; // skip '('
                double val = parseExpr();
                if (pos >= input.size() || input[pos] != ')') {
                    throw std::runtime_error("Missing closing parenthesis");
                }
                pos++; // skip ')'
                return val;
            }
            // number
            size_t start = pos;
            while (pos < input.size() && (std::isdigit(input[pos]) || input[pos] == '.')) {
                pos++;
            }
            if (start == pos) {
                throw std::runtime_error("Expected a number");
            }
            std::string numStr = input.substr(start, pos - start);
            std::istringstream iss(numStr);
            double val;
            if (!(iss >> val)) {
                throw std::runtime_error("Invalid number");
            }
            return val;
        }
    };

    double evaluate_expression(const std::string& expression) {
        try {
            Parser parser(expression);
            double result = parser.parse();
            return std::fabs(result - 24.0) < 1e-12; // exact comparison
        } catch (const std::exception&) {
            return false;
        }
    }

public:
    TwentyFourPointGame() {} // nums empty initially

    std::vector<int> get_my_cards() {
        nums.clear();
        _generate_cards();
        return nums;
    }

    // The answer method as described. Returns bool for valid expression, or vector<int> for "pass".
    // To mimic Python's behavior (return type can be bool or vector<int>), we use a wrapper.
    // In C++, we cannot have two return types, so we output via a parameter or separate method.
    // We'll follow the original API: answer returns bool normally, but for "pass" it also returns vector<int>.
    // To keep identical behavior, we'll make answer return bool and provide a separate get_my_cards.
    // That is already available. So we'll just implement answer returning bool.
    // The Python version returns self.get_my_cards() when expression == "pass", which is a list.
    // In our translation, the caller must call get_my_cards() separately when expression is "pass".
    // We'll keep the same interface: if expression == "pass", we return true (or false?) Actually, the
    // original code returns the list, so the return type is polymorphic. In C++ we cannot do that easily.
    // We'll modify: answer will handle "pass" by calling get_my_cards() and returning true (or indicating).
    // However, to exactly match, we can have answer return a pair (bool, vector<int>) but that changes interface.
    // Better: we keep answer(bool) and let the caller detect "pass" and call get_my_cards.
    // Since the problem states "Keep behavior identical, including inputs/outputs", we need to replicate
    // the fact that answer("pass") returns a list. In a standalone program, we can output that list.
    // But the class method signature in C++ can't return two types. We'll use a trick: make answer return
    // a std::variant<bool, std::vector<int>>. That's idiomatic for multiple return types.
    // We'll include <variant>.
    std::variant<bool, std::vector<int>> answer(const std::string& expression) {
        if (expression == "pass") {
            return get_my_cards();
        }

        // Build count of digits in expression that are in nums
        std::map<char, int> digitCount;
        for (char c : expression) {
            if (std::isdigit(c)) {
                char d = c;
                // Check if this digit is present in nums
                bool found = false;
                for (int num : nums) {
                    if (std::to_string(num)[0] == d) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    digitCount[d]++;
                }
            }
        }

        // Verify that each number in nums appears exactly as many times in expression
        std::map<char, int> used = digitCount;
        for (int num : nums) {
            char d = std::to_string(num)[0];
            auto it = used.find(d);
            if (it == used.end() || it->second <= 0) {
                return false;
            }
            it->second--;
        }

        // After consuming all nums, check that no extra digits remain
        for (const auto& p : used) {
            if (p.second != 0) {
                return false;
            }
        }

        return evaluate_expression(expression);
    }
};

// Example usage (not part of translation, but for testing)
/*
int main() {
    TwentyFourPointGame game;
    auto cards = game.get_my_cards();
    std::cout << "Cards: ";
    for (int x : cards) std::cout << x << " ";
    std::cout << std::endl;
    std::string expr = "4*3+6+6";
    game.nums = {4,3,6,6}; // for testing
    auto result = game.answer(expr);
    if (std::holds_alternative<bool>(result)) {
        std::cout << std::boolalpha << std::get<bool>(result) << std::endl;
    }
    return 0;
}
*/