#include <cctype>
#include <cmath>
#include <optional>
#include <string>
#include <vector>
#include <stdexcept>

class Calculator {
public:
    Calculator() = default;

    std::optional<double> calculate(const std::string& expression) {
        std::vector<double> operand_stack;
        std::vector<char> operator_stack;
        std::string num_buffer;

        for (char ch : expression) {
            if (std::isdigit(ch) || ch == '.') {
                num_buffer += ch;
            } else {
                if (!num_buffer.empty()) {
                    operand_stack.push_back(std::stod(num_buffer));
                    num_buffer.clear();
                }

                if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
                    while (!operator_stack.empty() &&
                           operator_stack.back() != '(' &&
                           precedence(operator_stack.back()) >= precedence(ch)) {
                        apply_operator(operand_stack, operator_stack);
                    }
                    operator_stack.push_back(ch);
                } else if (ch == '(') {
                    operator_stack.push_back(ch);
                } else if (ch == ')') {
                    while (!operator_stack.empty() && operator_stack.back() != '(') {
                        apply_operator(operand_stack, operator_stack);
                    }
                    if (!operator_stack.empty()) {
                        operator_stack.pop_back(); // remove '('
                    }
                }
                // ignore any other characters
            }
        }

        if (!num_buffer.empty()) {
            operand_stack.push_back(std::stod(num_buffer));
        }

        while (!operator_stack.empty()) {
            apply_operator(operand_stack, operator_stack);
        }

        if (operand_stack.empty()) {
            return std::nullopt;
        }
        return operand_stack.back();
    }

private:
    int precedence(char op) const {
        switch (op) {
            case '+':
            case '-': return 1;
            case '*':
            case '/': return 2;
            case '^': return 3;
            default:  return 0;
        }
    }

    void apply_operator(std::vector<double>& operand_stack,
                        std::vector<char>& operator_stack) const {
        char op = operator_stack.back();
        operator_stack.pop_back();

        double operand2 = operand_stack.back();
        operand_stack.pop_back();
        double operand1 = operand_stack.back();
        operand_stack.pop_back();

        double result;
        switch (op) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/':
                if (operand2 == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                result = operand1 / operand2;
                break;
            case '^':
                if (operand1 < 0 && std::fmod(operand2, 1.0) != 0.0) {
                    throw std::runtime_error("Negative base with fractional exponent");
                }
                result = std::pow(operand1, operand2);
                break;
            default:
                throw std::runtime_error("Unknown operator");
        }
        operand_stack.push_back(result);
    }
};