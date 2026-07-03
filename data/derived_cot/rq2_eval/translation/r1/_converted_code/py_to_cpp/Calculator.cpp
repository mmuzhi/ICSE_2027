#include <optional>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <map>
#include <functional>
#include <vector>
#include <iostream>

class Calculator {
private:
    std::map<char, std::function<double(double, double)>> operators;

    int precedence(char op) {
        static std::map<char, int> prec = {
            {'+', 1}, {'-', 1},
            {'*', 2}, {'/', 2},
            {'^', 3}
        };
        auto it = prec.find(op);
        return (it != prec.end()) ? it->second : 0;
    }

    void apply_operator(std::stack<double>& operands, std::stack<char>& ops) {
        char op = ops.top();
        ops.pop();
        double operand2 = operands.top();
        operands.pop();
        double operand1 = operands.top();
        operands.pop();
        double result = operators[op](operand1, operand2);
        operands.push(result);
    }

public:
    calculate() {
        operators = {
            {'+', [](double a, double b) { return a + b; }},
            {'-', [](double a, double b) { return a - b; }},
            {'*', [](double a, double b) { return a * b; }},
            {'/', [](double a, double b) { return a / b; }},
            {'^', [](double a, double b) { return std::pow(a, b); }}
        };
    }

    std::optional<double> calculate(const std::string& expression) {
        std::stack<double> operand_stack;
        std::stack<char> operator_stack;
        std::string num_buffer;

        for (char c : expression) {
            if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
                num_buffer += c;
            } else {
                if (!num_buffer.empty()) {
                    operand_stack.push(std::stod(num_buffer));
                    num_buffer.clear();
                }

                if (operators.find(c) != operators.end()) {
                    while (!operator_stack.empty() && 
                           operator_stack.top() != '(' && 
                           precedence(operator_stack.top()) >= precedence(c)) {
                        apply_operator(operand_stack, operator_stack);
                    }
                    operator_stack.push(c);
                } else if (c == '(') {
                    operator_stack.push(c);
                } else if (c == ')') {
                    while (!operator_stack.empty() && operator_stack.top() != '(') {
                        apply_operator(operand_stack, operator_stack);
                    }
                    if (!operator_stack.empty() && operator_stack.top() == '(') {
                        operator_stack.pop();
                    }
                }
            }
        }

        if (!num_buffer.empty()) {
            operand_stack.push(std::stod(num_buffer));
        }

        while (!operator_stack.empty()) {
            apply_operator(operand_stack, operator_stack);
        }

        if (operand_stack.empty()) {
            return std::nullopt;
        }
        return operand_stack.top();
    }
};