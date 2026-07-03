#include <deque>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <stdexcept>

class ExpressionCalculator {
private:
    std::deque<std::string> postfixStack;

    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    bool compare(char op1, char op2) {
        char cur_op = op1 == '%' ? '/' : op1;
        char peek_op = op2 == '%' ? '/' : op2;
        int operat_priority[8] = {0, 3, 2, 1, -1, 1, 0, 2};
        int idx_peek = peek_op - 40;
        int idx_cur = cur_op - 40;
        if (idx_peek < 0 || idx_peek >= 8 || idx_cur < 0 || idx_cur >= 8) {
            return false;
        }
        return operat_priority[idx_peek] >= operat_priority[idx_cur];
    }

    double _calculate(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            case '%': return std::fmod(a, b);
            default:
                throw std::invalid_argument("Unsupported operator: " + std::string(1, op));
        }
    }

    std::string transform(std::string expression) {
        expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
        for (char& c : expression) {
            if (c == '-') {
                c = '~';
            }
        }
        if (!expression.empty() && expression[0] == '~' && expression.size() > 1 && expression[1] == '(') {
            expression[0] = '-';
            return "0" + expression;
        }
        return expression;
    }

    void prepare(const std::string& expression) {
        postfixStack.clear();
        std::deque<char> operatorStack;
        int length = expression.length();
        for (int i = 0; i < length; i++) {
            char ch = expression[i];
            if (std::isdigit(static_cast<unsigned char>(ch)) || ch == '.') {
                std::string num;
                while (i < length && (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.')) {
                    num += expression[i];
                    i++;
                }
                i--;
                postfixStack.push_back(num);
            } else if (ch == '(') {
                operatorStack.push_front(ch);
            } else if (ch == ')') {
                while (!operatorStack.empty() && operatorStack.front() != '(') {
                    postfixStack.push_back(std::string(1, operatorStack.front()));
                    operatorStack.pop_front();
                }
                if (!operatorStack.empty()) {
                    operatorStack.pop_front();
                }
            } else if (isOperator(ch)) {
                while (!operatorStack.empty() && isOperator(operatorStack.front()) && !compare(operatorStack.front(), ch)) {
                    postfixStack.push_back(std::string(1, operatorStack.front()));
                    operatorStack.pop_front();
                }
                operatorStack.push_front(ch);
            }
        }
        while (!operatorStack.empty()) {
            postfixStack.push_back(std::string(1, operatorStack.front()));
            operatorStack.pop_front();
        }
    }

    double evaluatePostfix() {
        std::deque<double> stack;
        for (const std::string& token : postfixStack) {
            if (token.length() == 1 && isOperator(token[0])) {
                if (stack.size() < 2) {
                    throw std::runtime_error("Insufficient operands for operator");
                }
                double b = stack.front();
                stack.pop_front();
                double a = stack.front();
                stack.pop_front();
                stack.push_front(_calculate(a, b, token[0]));
            } else {
                try {
                    size_t pos;
                    double num = std::stod(token, &pos);
                    if (pos != token.length()) {
                        throw std::invalid_argument("Invalid token: " + token);
                    }
                    stack.push_front(num);
                } catch (const std::invalid_argument& e) {
                    throw std::invalid_argument("Invalid token: " + token);
                }
            }
        }
        if (stack.size() != 1) {
            throw std::runtime_error("Malformed expression");
        }
        return stack.front();
    }

public:
    ExpressionCalculator() {}

    double calculate(const std::string& expression) {
        std::string transformedExpression = transform(expression);
        prepare(transformedExpression);
        return evaluatePostfix();
    }
};