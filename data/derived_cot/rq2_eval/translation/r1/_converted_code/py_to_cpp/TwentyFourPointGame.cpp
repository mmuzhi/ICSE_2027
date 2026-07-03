#include <vector>
#include <cctype>
#include <stack>
#include <queue>
#include <map>
#include <cmath>
#include <string>
#include <variant>
#include <stdexcept>
#include <random>
#include <iostream>
#include <algorithm>

class TwentyFourPointGame {
private:
    std::vector<int> nums;

    void generate_cards() {
        nums.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 9);
        for (int i = 0; i < 4; ++i) {
            nums.push_back(dis(gen));
        }
    }

    using Token = std::variant<char, int>;

    std::vector<Token> tokenize(const std::string& expr) {
        std::vector<Token> tokens;
        int n = expr.length();
        int i = 0;
        while (i < n) {
            if (expr[i] == ' ') {
                i++;
                continue;
            }
            if (std::isdigit(expr[i])) {
                int num = expr[i] - '0';
                tokens.push_back(num);
                i++;
            } else if (expr[i] == '(') {
                tokens.push_back('(');
                i++;
            } else if (expr[i] == ')') {
                tokens.push_back(')');
                i++;
            } else {
                if (expr[i] == '-') {
                    if (tokens.empty()) {
                        tokens.push_back('u');
                        i++;
                    } else {
                        const Token& last_token = tokens.back();
                        if (std::holds_alternative<char>(last_token)) {
                            char c = std::get<char>(last_token);
                            if (c == '(' || c == '+' || c == '-' || c == '*' || c == '/') {
                                tokens.push_back('u');
                                i++;
                            } else {
                                tokens.push_back('-');
                                i++;
                            }
                        } else {
                            tokens.push_back('-');
                            i++;
                        }
                    }
                } else if (expr[i] == '+' || expr[i] == '*' || expr[i] == '/') {
                    tokens.push_back(expr[i]);
                    i++;
                } else {
                    throw std::runtime_error("Invalid character");
                }
            }
        }
        return tokens;
    }

    int get_precedence(char op) {
        if (op == 'u') {
            return 10;
        } else if (op == '*' || op == '/') {
            return 9;
        } else if (op == '+' || op == '-') {
            return 8;
        }
        return 0;
    }

    bool is_left_associative(char op) {
        return op != 'u';
    }

    std::vector<Token> shunting_yard(const std::vector<Token>& tokens) {
        std::vector<Token> output;
        std::stack<char> operators;

        for (const Token& token : tokens) {
            if (std::holds_alternative<int>(token)) {
                output.push_back(token);
            } else {
                char c = std::get<char>(token);
                if (c == '(') {
                    operators.push(c);
                } else if (c == ')') {
                    while (!operators.empty() && operators.top() != '(') {
                        output.push_back(operators.top());
                        operators.pop();
                    }
                    if (!operators.empty() && operators.top() == '(') {
                        operators.pop();
                    } else {
                        throw std::runtime_error("Mismatched parentheses");
                    }
                } else {
                    int prec = get_precedence(c);
                    while (!operators.empty() && operators.top() != '(') {
                        char top_op = operators.top();
                        int top_prec = get_precedence(top_op);
                        if (top_prec > prec || (top_prec == prec && is_left_associative(top_op))) {
                            output.push_back(top_op);
                            operators.pop();
                        } else {
                            break;
                        }
                    }
                    operators.push(c);
                }
            }
        }

        while (!operators.empty()) {
            if (operators.top() == '(') {
                throw std::runtime_error("Mismatched parentheses");
            }
            output.push_back(operators.top());
            operators.pop();
        }

        return output;
    }

    double evaluate_expression(const std::vector<Token>& rpn) {
        std::stack<double> stack;
        for (const Token& token : rpn) {
            if (std::holds_alternative<int>(token)) {
                stack.push(static_cast<double>(std::get<int>(token)));
            } else {
                char op = std::get<char>(token);
                if (op == 'u') {
                    if (stack.empty()) {
                        throw std::runtime_error("Not enough operands");
                    }
                    double a = stack.top();
                    stack.pop();
                    stack.push(-a);
                } else {
                    if (stack.size() < 2) {
                        throw std::runtime_error("Not enough operands");
                    }
                    double b = stack.top();
                    stack.pop();
                    double a = stack.top();
                    stack.pop();
                    double result = 0.0;
                    switch (op) {
                        case '+':
                            result = a + b;
                            break;
                        case '-':
                            result = a - b;
                            break;
                        case '*':
                            result = a * b;
                            break;
                        case '/':
                            if (std::abs(b) < 1e-9) {
                                throw std::runtime_error("Division by zero");
                            }
                            result = a / b;
                            break;
                        default:
                            throw std::runtime_error("Invalid operator");
                    }
                    stack.push(result);
                }
            }
        }
        if (stack.size() != 1) {
            throw std::runtime_error("Evaluation error");
        }
        return stack.top();
    }

public:
    TwentyFourPointGame() : nums() {}

    std::vector<int> get_my_cards() {
        nums.clear();
        generate_cards();
        return nums;
    }

    using AnswerResult = std::variant<std::vector<int>, bool>;

    AnswerResult answer(const std::string& expression) {
        if (expression == "pass") {
            return get_my_cards();
        }

        std::map<char, int> statistic;
        for (char c : expression) {
            if (std::isdigit(c)) {
                int num = c - '0';
                if (std::find(nums.begin(), nums.end(), num) != nums.end()) {
                    statistic[c]++;
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

        for (const auto& kv : nums_used) {
            if (kv.second != 0) {
                return false;
            }
        }

        try {
            std::vector<Token> tokens = tokenize(expression);
            std::vector<Token> rpn = shunting_yard(tokens);
            double result = evaluate_expression(rpn);
            if (std::abs(result - 24.0) < 1e-9) {
                return true;
            } else {
                return false;
            }
        } catch (...) {
            return false;
        }
    }
};