#include <vector>
#include <string>
#include <map>
#include <stack>
#include <random>
#include <cmath>
#include <stdexcept>
#include <variant>
#include <iostream>
#include <algorithm>

class TwentyFourPointGame {
private:
    std::vector<int> nums;
    void _generate_cards() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 9);
        nums.clear();
        for (int i = 0; i < 4; i++) {
            nums.push_back(distrib(gen));
        }
    }

public:
    std::vector<int> get_my_cards() {
        nums.clear();
        _generate_cards();
        return nums;
    }

    std::variant<std::vector<int>, bool> answer(const std::string& expression) {
        if (expression == "pass") {
            return get_my_cards();
        }

        std::map<std::string, int> nums_used;
        for (char c : expression) {
            if (std::isdigit(c)) {
                std::string s(1, c);
                nums_used[s]++;
            }
        }

        for (int num : nums) {
            std::string s = std::to_string(num);
            if (nums_used.find(s) != nums_used.end() && nums_used[s] > 0) {
                nums_used[s]--;
            } else {
                return false;
            }
        }

        bool all_zero = true;
        for (auto& pair : nums_used) {
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
            std::string expr = expression;
            for (auto& c : expr) {
                if (c == ' ') {
                    c = '\0';
                }
            }

            std::vector<std::string> tokens;
            std::string token;
            for (int i = 0; i < expr.length(); i++) {
                if (expr[i] == '\0') continue;
                if (std::isdigit(expr[i])) {
                    token += expr[i];
                } else {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token = "";
                    }
                    tokens.push_back(std::string(1, expr[i]));
                }
            }
            if (!token.empty()) {
                tokens.push_back(token);
            }

            std::map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
            std::stack<char> opStack;
            std::vector<std::string> output;

            for (auto& token : tokens) {
                if (token.size() == 1 && std::isdigit(token[0])) {
                    output.push_back(token);
                } else if (token == "(") {
                    opStack.push('(');
                } else if (token == ")") {
                    while (!opStack.empty() && opStack.top() != '(') {
                        output.push_back(std::string(1, opStack.top()));
                        opStack.pop();
                    }
                    if (opStack.empty()) {
                        throw std::runtime_error("Unmatched )");
                    }
                    opStack.pop();
                } else if (token.size() == 1 && precedence.find(token[0]) != precedence.end()) {
                    while (!opStack.empty() && opStack.top() != '(') {
                        char op2 = opStack.top();
                        if (precedence[op2] > precedence[token[0]] ||
                            (precedence[op2] == precedence[token[0]])) {
                            output.push_back(std::string(1, op2));
                            opStack.pop();
                        } else {
                            break;
                        }
                    }
                    opStack.push(token[0]);
                } else {
                    throw std::runtime_error("Unknown token: " + token);
                }
            }

            while (!opStack.empty()) {
                if (opStack.top() == '(') {
                    throw std::runtime_error("Unmatched (");
                }
                output.push_back(std::string(1, opStack.top()));
                opStack.pop();
            }

            std::stack<double> evalStack;
            for (auto& token : output) {
                if (token.size() == 1 && std::isdigit(token[0])) {
                    evalStack.push(std::stod(token));
                } else if (token.size() == 1 && token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
                    if (evalStack.size() < 2) {
                        throw std::runtime_error("Insufficient operands");
                    }
                    double b = evalStack.top(); evalStack.pop();
                    double a = evalStack.top(); evalStack.pop();
                    if (token[0] == '+') {
                        evalStack.push(a + b);
                    } else if (token[0] == '-') {
                        evalStack.push(a - b);
                    } else if (token[0] == '*') {
                        evalStack.push(a * b);
                    } else if (token[0] == '/') {
                        if (b == 0) {
                            throw std::runtime_error("Division by zero");
                        }
                        evalStack.push(a / b);
                    }
                }
            }

            if (evalStack.size() != 1) {
                throw std::runtime_error("Invalid RPN");
            }

            double result = evalStack.top();
            if (std::abs(result - 24.0) < 1e-10) {
                return true;
            }
            return false;
        } catch (...) {
            return false;
        }
    }
};