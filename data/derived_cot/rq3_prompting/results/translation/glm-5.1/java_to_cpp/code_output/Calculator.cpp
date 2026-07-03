#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <functional>
#include <optional>
#include <cmath>
#include <cctype>

class Calculator {
private:
    std::unordered_map<char, std::function<double(double, double)>> operators;

    int precedence(char op) {
        switch (op) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
            default:
                return 0;
        }
    }

    void applyOperator(std::stack<double>& operandStack, std::stack<char>& operatorStack) {
        char op = operatorStack.top();
        operatorStack.pop();
        double operand2 = operandStack.top();
        operandStack.pop();
        double operand1 = operandStack.top();
        operandStack.pop();
        double result = operators[op](operand1, operand2);
        operandStack.push(result);
    }

public:
    Calculator() {
        operators['+'] = [](double x, double y) { return x + y; };
        operators['-'] = [](double x, double y) { return x - y; };
        operators['*'] = [](double x, double y) { return x * y; };
        operators['/'] = [](double x, double y) { return x / y; };
        operators['^'] = [](double x, double y) { return std::pow(x, y); };
    }

    std::optional<double> calculate(const std::string& expression) {
        std::stack<double> operandStack;
        std::stack<char> operatorStack;
        std::string numBuffer;

        for (size_t i = 0; i < expression.length(); i++) {
            char ch = expression[i];
            if (std::isdigit(static_cast<unsigned char>(ch)) || ch == '.') {
                numBuffer += ch;
            } else {
                if (numBuffer.length() > 0) {
                    operandStack.push(std::stod(numBuffer));
                    numBuffer.clear();
                }

                if (operators.find(ch) != operators.end()) {
                    while (!operatorStack.empty() &&
                           operatorStack.top() != '(' &&
                           precedence(operatorStack.top()) >= precedence(ch)) {
                        applyOperator(operandStack, operatorStack);
                    }
                    operatorStack.push(ch);
                } else if (ch == '(') {
                    operatorStack.push(ch);
                } else if (ch == ')') {
                    while (!operatorStack.empty() && operatorStack.top() != '(') {
                        applyOperator(operandStack, operatorStack);
                    }
                    operatorStack.pop();
                }
            }
        }

        if (numBuffer.length() > 0) {
            operandStack.push(std::stod(numBuffer));
        }

        while (!operatorStack.empty()) {
            applyOperator(operandStack, operatorStack);
        }

        return operandStack.empty() ? std::optional<double>{} : operandStack.top();
    }
};

int main() {
    Calculator calculator;
    auto result = calculator.calculate("1+2-3");
    if (result.has_value()) {
        std::cout << result.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
    return 0;
}