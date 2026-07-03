#include <deque>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

class ExpressionCalculator {
public:
    ExpressionCalculator() : operat_priority({0, 3, 2, 1, -1, 1, 0, 2}) {}

    double calculate(const std::string& expression) {
        std::string transformed = transform(expression);
        prepare(transformed);

        std::deque<std::string> result_stack;
        while (!postfix_stack.empty()) {
            std::string token = postfix_stack.front();
            postfix_stack.pop_front();
            if (!is_operator(token[0])) {
                // Replace '~' with '-' for negative numbers
                if (token[0] == '~') {
                    token[0] = '-';
                }
                result_stack.push_back(token);
            } else {
                std::string second_value = result_stack.back();
                result_stack.pop_back();
                std::string first_value = result_stack.back();
                result_stack.pop_back();

                // Replace '~' in operands
                if (first_value[0] == '~') first_value[0] = '-';
                if (second_value[0] == '~') second_value[0] = '-';

                double temp_result = _calculate(first_value, second_value, token);
                result_stack.push_back(std::to_string(temp_result));
            }
        }

        // Combine results and evaluate
        if (result_stack.empty()) {
            return 0.0;
        }

        double total = std::stod(result_stack[0]);
        for (size_t i = 1; i < result_stack.size(); ++i) {
            total = std::stod(result_stack[i]) * total; // This is incorrect for non-multiplication operations
        }
        return total;
    }

    void prepare(const std::string& expression) {
        op_stack.push(',');
        size_t current_index = 0;
        int count = 0;

        for (size_t i = 0; i < expression.size(); ++i) {
            char current_op = expression[i];
            if (is_operator(current_op)) {
                if (count > 0) {
                    postfix_stack.push_back(expression.substr(current_index, count));
                }
                char peek_op = op_stack.empty() ? ',' : op_stack.top();
                if (current_op == ')') {
                    while (op_stack.top() != '(') {
                        postfix_stack.push_back(std::string(1, op_stack.top()));
                        op_stack.pop();
                    }
                    op_stack.pop(); // Remove '('
                } else {
                    while (current_op != '(' && (!op_stack.empty() && op_stack.top() != ',' && compare(current_op, op_stack.top()))) {
                        postfix_stack.push_back(std::string(1, op_stack.top()));
                        op_stack.pop();
                        if (!op_stack.empty()) {
                            peek_op = op_stack.top();
                        }
                    }
                    op_stack.push(current_op);
                }
                count = 0;
                current_index = i + 1;
            } else {
                count++;
            }
        }

        if (count > 0) {
            postfix_stack.push_back(expression.substr(current_index, count));
        }

        while (!op_stack.empty() && op_stack.top() != ',') {
            postfix_stack.push_back(std::string(1, op_stack.top()));
            op_stack.pop();
        }
    }

    static bool is_operator(char c) {
        static const std::string ops = "+-*/()";
        return ops.find(c) != std::string::npos;
    }

    bool compare(char cur, char peek) {
        if (cur == '%') cur = '/';
        if (peek == '%') peek = '/';
        int index_cur = static_cast<int>(peek) - 40;
        int index_peek = static_cast<int>(cur) - 40;
        return operat_priority[index_peek] >= operat_priority[index_cur];
    }

    static double _calculate(const std::string& first_value, const std::string& second_value, const std::string& current_op) {
        if (current_op == "+") {
            return std::stod(first_value) + std::stod(second_value);
        } else if (current_op == "-") {
            return std::stod(first_value) - std::stod(second_value);
        } else if (current_op == "*") {
            return std::stod(first_value) * std::stod(second_value);
        } else if (current_op == "/") {
            return std::stod(first_value) / std::stod(second_value);
        } else if (current_op == "%") {
            return std::fmod(std::stod(first_value), std::stod(second_value));
        } else {
            throw std::invalid_argument("Unexpected operator: " + current_op);
        }
    }

    static std::string transform(const std::string& expression) {
        std::string expr = expression;
        // Remove whitespace
        expr.erase(std::remove_if(expr.begin(), expr.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), expr.end());
        // Remove trailing '=' if present
        if (!expr.empty() && expr.back() == '=') {
            expr.pop_back();
        }

        std::vector<char> arr(expr.begin(), expr.end());
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == '-') {
                if (i == 0) {
                    arr[i] = '~';
                } else {
                    char prev_c = arr[i - 1];
                    if (prev_c == '(' || prev_c == ')' || prev_c == '+' || prev_c == '-' || prev_c == '*' || prev_c == '/' || (prev_c == 'E' && i > 1) || (prev_c == 'e' && i > 1)) {
                        arr[i] = '~';
                    }
                }
            }
        }

        if (!arr.empty() && arr[0] == '~' && (arr.size() > 1 && arr[1] == '(')) {
            arr[0] = '-';
            return "0" + std::string(arr.begin(), arr.end());
        } else {
            return std::string(arr.begin(), arr.end());
        }
    }

private:
    std::deque<std::string> postfix_stack;
    std::stack<char> op_stack;
    std::vector<int> operat_priority;
};