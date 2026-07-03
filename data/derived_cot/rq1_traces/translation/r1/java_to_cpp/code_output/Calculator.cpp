#include <iostream>
#include <stack>
#include <map>
#include <functional>
#include <cctype>
#include <cmath>
#include <optional>
#include <string>
#include <stdexcept>

class Calculator {
private:
    std::map<char, std::function<double(double, double)>> operators;

    int precedence(char op) {
        switch(op) {
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
        if (operatorStack.empty()) {
            throw std::runtime_error("Operator stack is empty");
        }
        char op = operatorStack.top();
        operatorStack.pop();

        if (operandStack.size() < 2) {
            throw std::runtime_error("Not enough operands");
        }
        double operand2 = operandStack.top();
        operandStack.pop();
        double operand1 = operandStack.top();
        operandStack.pop();

        double result = operators.at(op)(operand1, operand2);
        operandStack.push(result);
    }

public:
    Calculator() {
        operators['+'] = [](double a, double b) { return a + b; };
        operators['-'] = [](double a, double b) { return a - b; };
        operators['*'] = [](double a, double b) { return a * b; };
        operators['/'] = [](double a, double b) { return a / b; };
        operators['^'] = [](double a, double b) { return std::pow(a, b); };
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
                if (!numBuffer.empty()) {
                    operandStack.push(std::stod(numBuffer));
                    numBuffer.clear();
                }

                if (operators.find(ch) != operators.end()) {
                    while (!operatorStack.empty() && operatorStack.top() != '(' &&
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
                    if (!operatorStack.empty() && operatorStack.top() == '(') {
                        operatorStack.pop();
                    }
                }
            }
        }

        if (!numBuffer.empty()) {
            operandStack.push(std::stod(numBuffer));
        }

        while (!operatorStack.empty()) {
            applyOperator(operandStack, operatorStack);
        }

        if (operandStack.empty()) {
            return std::nullopt;
        } else {
            return operandStack.top();
        }
    }
};

int main() {
    Calculator calculator;
    auto result = calculator.calculate("1+2-3");
    if (result) {
        std::cout << *result << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
    return 0;
}