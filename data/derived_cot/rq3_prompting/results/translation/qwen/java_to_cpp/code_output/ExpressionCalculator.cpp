#include <deque>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>

class ExpressionCalculator {
private:
    std::deque<std::string> postfixStack;

    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
    }

    int getPrecedence(char op) {
        if (op == '*' || op == '/' || op == '%') 
            return 2;
        if (op == '+' || op == '-')
            return 1;
        return 0;
    }

    bool compare(char op1, char op2) {
        int prec1 = getPrecedence(op1);
        int prec2 = getPrecedence(op2);
        return prec1 >= prec2;
    }

    double _calculate(double a, double b, char operator) {
        switch (operator) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            case '%': return fmod(a, b);
            default: throw std::invalid_argument("Unsupported operator: " + std::string(1, operator));
        }
    }

public:
    ExpressionCalculator() : postfixStack() {}

    double calculate(const std::string& expression) {
        std::string transformed = transform(expression);
        prepare(transformed);
        return evaluatePostfix();
    }

    void prepare(const std::string& expression) {
        postfixStack.clear();
        std::stack<char> opStack;

        for (int i = 0; i < expression.length(); ) {
            char ch = expression[i];
            if (isdigit(ch) || ch == '.') {
                std::string numStr;
                int j = i;
                while (j < expression.length() && (isdigit(expression[j]) || expression[j] == '.')) {
                    numStr += expression[j];
                    j++;
                }
                postfixStack.push_back(numStr);
                i = j;
            } else if (ch == '(') {
                opStack.push(ch);
                i++;
            } else if (ch == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    postfixStack.push_back(std::string(1, opStack.top()));
                    opStack.pop();
                }
                if (!opStack.empty()) {
                    opStack.pop();
                }
                i++;
            } else if (isOperator(ch)) {
                while (!opStack.empty() && isOperator(opStack.top()) && !compare(opStack.top(), ch)) {
                    postfixStack.push_back(std::string(1, opStack.top()));
                    opStack.pop();
                }
                opStack.push(ch);
                i++;
            } else {
                i++;
            }
        }
        while (!opStack.empty()) {
            postfixStack.push_back(std::string(1, opStack.top()));
            opStack.pop();
        }
    }

    double evaluatePostfix() {
        std::stack<double> evalStack;
        for (const std::string& token : postfixStack) {
            if (isOperator(token[0])) {
                double b = evalStack.top(); evalStack.pop();
                double a = evalStack.top(); evalStack.pop();
                evalStack.push(_calculate(a, b, token[0]));
            } else {
                evalStack.push(std::stod(token));
            }
        }
        return evalStack.top();
    }

    std::string transform(const std::string& expression) {
        std::string expr = expression;
        expr.erase(std::remove_if(expr.begin(), expr.end(), [](unsigned char c) { return std::isspace(c); }), expr.end());
        for (char& c : expr) {
            if (c == '-') {
                c = '~';
            }
        }
        if (!expr.empty() && expr[0] == '~' && expr.length() > 1 && expr[1] == '(') {
            expr[0] = '-';
            expr = "0" + expr;
        }
        return expr;
    }
};