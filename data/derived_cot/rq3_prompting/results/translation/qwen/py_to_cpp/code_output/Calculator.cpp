#include <stack>
#include <string>
#include <cmath>
#include <optional>
#include <map>
#include <cctype>

class Calculator {
private:
    std::map<char, std::function<double(double, double)>> operators;

    int precedence(char op) {
        switch (op) {
            case '+': case '-': return 1;
            case '*': case '/': return 2;
            case '^': return 3;
            default: return 0;
        }
    }

    std::pair<std::stack<double>, std::stack<char>> apply_operator(
        std::stack<double>& operand_stack, 
        std::stack<char>& operator_stack
    ) {
        char op = operator_stack.top();
        operator_stack.pop();

        double operand2 = operand_stack.top();
        operand_stack.pop();
        double operand1 = operand_stack.top();
        operand_stack.pop();

        if (op == '^') {
            operand_stack.push(std::pow(operand1, operand2));
        } else {
            operand_stack.push(operators[op](operand1, operand2));
        }

        return {operand_stack, operator_stack};
    }

public:
    Calculator() {
        operators = {
            {'+', [](double x, double y) { return x + y; }},
            {'-', [](double x, double y) { return x - y; }},
            {'*', [](double x, double y) { return x * y; }},
            {'/', [](double x, double y) { 
                if (y == 0) return std::numeric_limits<double>::quiet_NaN(); 
                return x / y; 
            }},
            {'^', [](double x, double y) { return std::pow(x, y); }}
        };
    }

    std::optional<double> calculate(const std::string& expression) {
        std::stack<double> operand_stack;
        std::stack<char> operator_stack;
        std::string num_buffer;

        for (char c : expression) {
            if (std::isdigit(c) || c == '.') {
                num_buffer += c;
            } else {
                if (!num_buffer.empty()) {
                    operand_stack.push(std::stod(num_buffer));
                    num_buffer.clear();
                }

                if (c == '(') {
                    operator_stack.push(c);
                } else if (c == ')') {
                    while (!operator_stack.empty() && operator_stack.top() != '(') {
                        auto result = apply_operator(operand_stack, operator_stack);
                        operand_stack = std::get<0>(result);
                        operator_stack = std::get<1>(result);
                    }
                    if (!operator_stack.empty() && operator_stack.top() == '(') {
                        operator_stack.pop();
                    }
                } else if (c == '^' || c == '*' || c == '/' || c == '+' || c == '-') {
                    while (!operator_stack.empty() && operator_stack.top() != '(' && 
                           precedence(operator_stack.top()) >= precedence(c)) {
                        auto result = apply_operator(operand_stack, operator_stack);
                        operand_stack = std::get<0>(result);
                        operator_stack = std::get<1>(result);
                    }
                    operator_stack.push(c);
                }
            }
        }

        if (!num_buffer.empty()) {
            operand_stack.push(std::stod(num_buffer));
        }

        while (!operator_stack.empty()) {
            auto result = apply_operator(operand_stack, operator_stack);
            operand_stack = std::get<0>(result);
            operator_stack = std::get<1>(result);
        }

        if (operand_stack.size() != 1) {
            return std::nullopt;
        }

        double result = operand_stack.top();
        if (std::isnan(result)) {
            return std::nullopt;
        }

        return result;
    }
};