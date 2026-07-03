#include <deque>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <regex>

class ExpressionCalculator {
private:
    std::deque<std::string> postfix_stack;
    int operat_priority[8] = {0, 3, 2, 1, -1, 1, 0, 2}; // [0, 3, 2, 1, -1, 1, 0, 2]

    static bool is_operator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '%';
    }

    bool compare(char cur, char peek) {
        if (cur == '%') cur = '/';
        if (peek == '%') peek = '/';
        int index_peek = static_cast<int>(peek) - 40;
        int index_cur = static_cast<int>(cur) - 40;
        return operat_priority[index_peek] >= operat_priority[index_cur];
    }

    static double _calculate(const std::string& first_value, const std::string& second_value, char current_op) {
        double first = std::stod(first_value);
        double second = std::stod(second_value);
        switch (current_op) {
            case '+': return first + second;
            case '-': return first - second;
            case '*': return first * second;
            case '/': return first / second;
            case '%': return fmod(first, second);
            default: throw std::runtime_error("Unexpected operator: " + std::string(1, current_op));
        }
    }

    static std::string transform(const std::string& expression) {
        std::string expr = std::regex_replace(expression, std::regex("\\s+"), "");
        expr = std::regex_replace(expr, std::regex("=")$, "");
        std::vector<char> arr(expr.begin(), expr.end());

        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == '-') {
                if (i == 0) {
                    arr[i] = '~';
                } else {
                    char prev = arr[i-1];
                    if (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '(') {
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

public:
    ExpressionCalculator() {}

    double calculate(const std::string& expression) {
        std::string transformed = transform(expression);
        prepare(transformed);
        std::deque<std::string> result_stack;

        // Reverse the postfix_stack to evaluate from left to right
        std::deque<std::string> eval_stack(postfix_stack.rbegin(), postfix_stack.rend());

        while (!eval_stack.empty()) {
            std::string token = eval_stack.front();
            eval_stack.pop_front();

            if (!is_operator(token[0])) {
                // Replace '~' with '-' for negative numbers
                if (token[0] == '~') {
                    token[0] = '-';
                }
                result_stack.push_back(token);
            } else {
                if (token[0] == '~') {
                    token[0] = '/';
                }
                std::string second_value = result_stack.back();
                result_stack.pop_back();
                std::string first_value = result_stack.back();
                result_stack.pop_back();

                double temp_result = _calculate(first_value, second_value, token[0]);
                result_stack.push_back(std::to_string(temp_result));
            }
        }

        // If there's only one number left, return it
        if (result_stack.size() == 1) {
            return std::stod(result_stack[0]);
        }

        throw std::runtime_error("Invalid expression");
    }

    void prepare(const std::string& expression) {
        std::deque<char> op_stack;
        op_stack.push_back(',');
        size_t current_index = 0;
        int count = 0;

        for (size_t i = 0; i < expression.length(); ++i) {
            char current_op = expression[i];
            if (is_operator(current_op)) {
                if (count > 0) {
                    std::string num = expression.substr(current_index, count);
                    postfix_stack.push_back(num);
                    count = 0;
                }
                char peek_op = op_stack.empty() ? ',' : op_stack.back();
                if (current_op == ')') {
                    while (!op_stack.empty() && op_stack.back() != '(') {
                        postfix_stack.push_back(op_stack.back());
                        op_stack.pop_back();
                    }
                    if (!op_stack.empty() && op_stack.back() == '(') {
                        op_stack.pop_back();
                    }
                } else {
                    while (!op_stack.empty() && op_stack.back() != ',' && compare(current_op, op_stack.back())) {
                        postfix_stack.push_back(op_stack.back());
                        op_stack.pop_back();
                    }
                    op_stack.push_back(current_op);
                }
                current_index = i + 1;
                count = 0;
            } else {
                count++;
            }
        }

        if (count > 0) {
            std::string num = expression.substr(current_index, count);
            postfix_stack.push_back(num);
        }

        while (!op_stack.empty() && op_stack.front() != ',') {
            postfix_stack.push_back(op_stack.front());
            op_stack.pop_front();
        }
    }
};