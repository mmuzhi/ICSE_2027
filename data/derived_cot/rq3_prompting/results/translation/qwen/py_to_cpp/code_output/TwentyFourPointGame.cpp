#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <stack>
#include <map>
#include <stdexcept>

class TwentyFourPointGame {
private:
    std::vector<int> nums;
    void _generate_cards() {
        // Use random_device for better randomness
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 9);
        nums.clear();
        for (int i = 0; i < 4; i++) {
            nums.push_back(distrib(gen));
        }
    }

    std::vector<std::string> tokenize(const std::string& expression) {
        std::vector<std::string> tokens;
        std::string token;
        for (char c : expression) {
            if (isspace(c)) continue;
            if (isdigit(c)) {
                token += c;
            } else {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
                    tokens.push_back(std::string(1, c));
                } else {
                    throw std::runtime_error("Unknown character in expression: " + std::string(1, c));
                }
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::vector<std::string> shunting_yard(const std::vector<std::string>& tokens) {
        std::vector<std::string> output;
        std::stack<std::string> operators;
        std::map<std::string, int> precedence = {
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2},
            {"(", 0}
        };
        for (const auto& token : tokens) {
            if (token.size() == 1 && isdigit(token[0])) {
                output.push_back(token);
            } else if (token.size() > 1) {
                if (std::all_of(token.begin(), token.end(), [](unsigned char c) { return isdigit(c); })) {
                    output.push_back(token);
                } else {
                    throw std::runtime_error("Invalid token: " + token);
                }
            } else if (token == "(") {
                operators.push(token);
            } else if (token == ")") {
                while (!operators.empty() && operators.top() != "(") {
                    output.push_back(operators.top());
                    operators.pop();
                }
                if (operators.top() == "(") {
                    operators.pop();
                }
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                while (!operators.empty() && precedence.find(operators.top()) != precedence.end() && 
                       precedence[operators.top()] >= precedence[token]) {
                    output.push_back(operators.top());
                    operators.pop();
                }
                operators.push(token);
            }
        }
        while (!operators.empty()) {
            output.push_back(operators.top());
            operators.pop();
        }
        return output;
    }

    double evaluate_rpn(const std::vector<std::string>& rpn) {
        std::stack<double> stack;
        for (const auto& token : rpn) {
            if (std::all_of(token.begin(), token.end(), [](unsigned char c) { return isdigit(c); })) {
                int num = std::stoi(token);
                stack.push(num);
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (stack.size() < 2) {
                    return 0.0;
                }
                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();
                double result;
                if (token == "+") {
                    result = a + b;
                } else if (token == "-") {
                    result = a - b;
                } else if (token == "*") {
                    result = a * b;
                } else if (token == "/") {
                    if (b == 0) {
                        return 0.0;
                    }
                    result = a / b;
                } else {
                    return 0.0;
                }
                stack.push(result);
            } else {
                throw std::runtime_error("Unknown token: " + token);
            }
        }
        if (stack.size() != 1) {
            return 0.0;
        }
        return stack.top();
    }

public:
    TwentyFourPointGame() {
        nums = std::vector<int>();
    }

    void get_my_cards() {
        nums.clear();
        _generate_cards();
    }

    std::vector<int> answer(const std::string& expression) {
        if (expression == "pass") {
            get_my_cards();
            return nums;
        }
        std::map<char, int> statistic;
        for (char c : expression) {
            if (isdigit(c)) {
                int num = c - '0';
                if (num >= 1 && num <= 9 && std::find(nums.begin(), nums.end(), num) != nums.end()) {
                    statistic[c] = statistic.get(c, 0) + 1;
                }
            }
        }
        std::map<char, int> nums_used = statistic;
        for (int num : nums) {
            char c = '0' + num;
            if (nums_used.find(c) != nums_used.end() && nums_used[c] > 0) {
                nums_used[c]--;
            } else {
                return false;
            }
        }
        bool all_zero = true;
        for (auto& kv : nums_used) {
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
            std::vector<std::string> tokens = tokenize(expression);
            std::vector<std::string> rpn = shunting_yard(tokens);
            double result = evaluate_rpn(rpn);
            if (std::abs(result - 24) < 1e-6) {
                return true;
            } else {
                return false;
            }
        } catch (...) {
            return false;
        }
    }
};