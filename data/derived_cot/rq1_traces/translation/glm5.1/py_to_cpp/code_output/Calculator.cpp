#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <optional>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <utility>

class Calculator {
public:
    Calculator() {
        operators = {
            {'+', [](double x, double y) { return x + y; }},
            {'-', [](double x, double y) { return x - y; }},
            {'*', [](double x, double y) { return x * y; }},
            {'/', [](double x, double y) { return x / y; }},
            {'^', [](double x, double y) { return std::pow(x, y); }}
        };
    }

    std::optional<double> calculate(const std::string& expression) {
        std::vector<double> operand_stack;
        std::vector<char> operator_stack;
        std::string num_buffer;

        for (char c : expression) {
            if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
                num_buffer += c;
            } else {
                if (!num_buffer.empty()) {
                    size_t pos;
                    double val = std::stod(num_buffer, &pos);
                    if (pos != num_buffer.length()) {
                        throw std::invalid_argument("Invalid number format");
                    }
                    operand_stack.push_back(val);
                    num_buffer.clear();
                }

                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                    while (!operator_stack.empty() &&
                           operator_stack.back() != '(' &&
                           precedence(operator_stack.back()) >= precedence(c)) {
                        apply_operator(operand_stack, operator_stack);
                    }
                    operator_stack.push_back(c);
                } else if (c == '(') {
                    operator_stack.push_back(c);
                } else if (c == ')') {
                    while (!operator_stack.empty() && operator_stack.back() != '(') {
                        apply_operator(operand_stack, operator_stack);
                    }
                    if (operator_stack.empty()) {
                        throw std::out_of_range("Mismatched parentheses");
                    }
                    operator_stack.pop_back();
                }
            }
        }

        if (!num_buffer.empty()) {
            size_t pos;
            double val = std::stod(num_buffer, &pos);
            if (pos != num_buffer.length()) {
                throw std::invalid_argument("Invalid number format");
            }
            operand_stack.push_back(val);
        }

        while (!operator_stack.empty()) {
            apply_operator(operand_stack, operator_stack);
        }

        if (!operand_stack.empty()) {
            return operand_stack.back();
        }
        return std::nullopt;
    }

    int precedence(char op) const {
        static const std::unordered_map<char, int> prec = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'^', 3}
        };
        auto it = prec.find(op);
        if (it != prec.end()) {
            return it->second;
        }
        return 0;
    }

    std::pair<std::vector<double>&, std::vector<char>&> apply_operator(std::vector<double>& operand_stack, std::vector<char>& operator_stack) {
        if (operator_stack.empty()) {
            throw std::out_of_range("operator_stack is empty");
        }
        char op = operator_stack.back();
        operator_stack.pop_back();

        if (operand_stack.size() < 2) {
            throw std::out_of_range("operand_stack has insufficient elements");
        }
        double operand2 = operand_stack.back();
        operand_stack.pop_back();

        double operand1 = operand_stack.back();
        operand_stack.pop_back();

        double result = operators[op](operand1, operand2);
        operand_stack.push_back(result);

        return {operand_stack, operator_stack};
    }

private:
    std::unordered_map<char, std::function<double(double, double)>> operators;
};