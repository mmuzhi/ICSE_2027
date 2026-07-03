#include <string>
#include <deque>
#include <stack>
#include <cctype>
#include <cmath>
#include <vector>

class ExpressionCalculator {
private:
    std::deque<std::string> postfixStack;

    bool is_operator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    bool compare(char op1, char op2) {
        char cur_op = op1 == '%' ? '/' : op1;
        char peek_op = op2 == '%' ? '/' : op2;
        int priorities[] = {0, 3, 2, 1, -1, 1, 0, 2}; // Corresponds to operators +, -, *, /, %, (, )
        return priorities[peek_op - 40] >= priorities[cur_op - 40];
    }

    double _calculate(double a, double b, char operator_char) {
        switch (operator_char) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            case '%': return std::fmod(a, b); // Use std::fmod for modulo operation
            default: throw std::invalid_argument("Unsupported operator: " + std::string(1, operator_char));
        }
    }

    void prepare(const std::string& expression) {
        postfixStack.clear();
        std::stack<char> operatorStack;

        for (int i = 0; i < expression.length(); ++i) {
            char ch = expression[i];
            if (std::isdigit(ch) || ch == '.') {
                std::string num;
                while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                    num += expression[i];
                    ++i;
                }
                --i; // Adjust index after inner loop
                postfixStack.push_back(num);
            } else if (ch == '(') {
                operatorStack.push(ch);
            } else if (ch == ')') {
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfixStack.push_back(std::string(1, operatorStack.top()));
                    operatorStack.pop();
                }
                if (!operatorStack.empty()) operatorStack.pop(); // Remove '('
            } else if (isOperator(ch)) {
                while (!operatorStack.empty() && isOperator(operatorStack.top()) && compare(operatorStack.top(), ch)) {
                    postfixStack.push_back(std::string(1, operatorStack.top()));
                    operatorStack.pop();
                }
                operatorStack.push(ch);
            }
        }

        while (!operatorStack.empty()) {
            postfixStack.push_back(std::string(1, operatorStack.top()));
            operatorStack.pop();
        }
    }

    std::string transform(const std::string& expression) {
        std::string result = expression;
        // Remove spaces
        result.erase(std::remove_if(result.begin(), result.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), result.end());
        // Handle negative numbers at the start or after '('
        if (result.size() > 0 && result[0] == '~' && result.size() > 1 && result[1] == '(') {
            result[0] = '-';
            return "0" + result;
        }
        return result;
    }

public:
    ExpressionCalculator() {}

    double calculate(const std::string& expression) {
        std::string transformed = transform(expression);
        prepare(transformed);
        return evaluatePostfix();
    }

    double evaluatePostfix() {
        std::stack<double> stack;
        for (const auto& token : postfixStack) {
            if (isOperator(token[0])) {
                double b = stack.top(); stack.pop();
                double a = stack.top(); stack.pop();
                stack.push(_calculate(a, b, token[0]));
            } else {
                stack.push(std::stod(token));
            }
        }
        return stack.top();
    }
};