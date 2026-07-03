#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <map>
#include <functional>
#include <utility>

class Calculator {
private:
    std::map<char, std::function<double(double, double)>> operators;

    int precedence(char op) {
        if (op == '^') return 3;
        else if (op == '*' || op == '/') return 2;
        else if (op == '+' || op == '-') return 1;
        return 0;
    }

    std::pair<std::vector<double>, std::vector<char>> apply_operator(std::vector<double>& operand_stack, std::vector<char>& operator_stack) {
        char op = operator_stack.back();
        operator_stack.pop_back();
        double operand2 = operand_stack.back();
        operand_stack.pop_back();
        double operand1 = operand_stack.back();
        operand_stack.pop_back();

        double result = operators[op](operand1, operand2);
        operand_stack.push_back(result);
        return std::make_pair(operand_stack, operator_stack);
    }

public:
    Calculator() {
        operators['+'] = [](double x, double y) { return x + y; };
        operators['-'] = [](double x, double y) { return x - y; };
        operators['*'] = [](double x, double y) { return x * y; };
        operators['/'] = [](double x, double y) {
            if (y == 0) throw std::runtime_error("Division by zero");
            return x / y;
        };
        operators['^'] = [](double x, double y) { return std::pow(x, y); };
    }

    double calculate(const std::string& expression) {
        if (expression.empty()) {
            throw std::runtime_error("Empty expression");
        }

        std::vector<double> operand_stack;
        std::vector<char> operator_stack;
        std::string num_buffer;

        for (char c : expression) {
            if (std::isdigit(c) || c == '.') {
                num_buffer += c;
            } else {
                if (!num_buffer.empty()) {
                    try {
                        operand_stack.push_back(std::stod(num_buffer));
                    } catch (...) {
                        throw std::runtime_error("Invalid number format");
                    }
                    num_buffer = "";
                }

                if (c == '(') {
                    operator_stack.push_back(c);
                } else if (c == ')') {
                    while (!operator_stack.empty() && operator_stack.back() != '(') {
                        operand_stack, operator_stack = apply_operator(operand_stack, operator_stack);
                    }
                    if (!operator_stack.empty() && operator_stack.back() == '(') {
                        operator_stack.pop_back();
                    }
                } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                    while (!operator_stack.empty() && operator_stack.back() != '(') {
                        char top_op = operator_stack.back();
                        if (precedence(top_op) >= precedence(c)) {
                            operand_stack, operator_stack = apply_operator(operand_stack, operator_stack);
                        } else {
                            break;
                        }
                    }
                    operator_stack.push_back(c);
                }
            }
        }

        if (!num_buffer.empty()) {
            try {
                operand_stack.push_back(std::stod(num_buffer));
            } catch (...) {
                throw std::runtime_error("Invalid number format");
            }
        }

        while (!operator_stack.empty()) {
            operand_stack, operator_stack = apply_operator(operand_stack, operator_stack);
        }

        if (operand_stack.empty()) {
            throw std::runtime_error("Invalid expression");
        }

        return operand_stack.back();
    }
};