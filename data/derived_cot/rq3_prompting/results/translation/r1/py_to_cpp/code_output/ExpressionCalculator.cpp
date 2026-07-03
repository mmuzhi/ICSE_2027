#include <deque>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <regex>
#include <array>

class ExpressionCalculator {
public:
    ExpressionCalculator() : operat_priority{0, 3, 2, 1, -1, 1, 0, 2} {}

    double calculate(const std::string& expression) {
        std::string prepared = prepare(transform(expression));
        // postfix_stack is now filled by prepare()
        std::deque<std::string> result_stack;

        // Reverse to pop from original left (postfix evaluation order)
        std::reverse(postfix_stack.begin(), postfix_stack.end());

        while (!postfix_stack.empty()) {
            std::string current_op = postfix_stack.back();
            postfix_stack.pop_back();
            if (!is_operator(current_op)) {
                // Replace tilde with minus for negative numbers
                std::string num = current_op;
                std::replace(num.begin(), num.end(), '~', '-');
                result_stack.push_back(num);
            } else {
                std::string second_value = result_stack.back(); result_stack.pop_back();
                std::string first_value = result_stack.back(); result_stack.pop_back();
                std::replace(first_value.begin(), first_value.end(), '~', '-');
                std::replace(second_value.begin(), second_value.end(), '~', '-');

                double temp_result = _calculate(first_value, second_value, current_op);
                result_stack.push_back(std::to_string(temp_result));
            }
        }

        // Final evaluation: multiply all items in result_stack (simulate eval("*".join(...)))
        double product = 1.0;
        while (!result_stack.empty()) {
            product *= std::stod(result_stack.front());
            result_stack.pop_front();
        }
        return product;
    }

    std::string prepare(const std::string& expression) {
        postfix_stack.clear();
        std::deque<char> op_stack;
        op_stack.push_back(','); // marker

        std::vector<char> arr(expression.begin(), expression.end());
        size_t current_index = 0;
        int count = 0;

        for (size_t i = 0; i < arr.size(); ++i) {
            char current_op = arr[i];
            if (is_operator(std::string(1, current_op))) {
                if (count > 0) {
                    postfix_stack.push_back(std::string(arr.begin() + current_index, arr.begin() + current_index + count));
                }
                char peek_op = op_stack.back();
                if (current_op == ')') {
                    while (op_stack.back() != '(') {
                        postfix_stack.push_back(std::string(1, op_stack.back()));
                        op_stack.pop_back();
                    }
                    op_stack.pop_back(); // remove '('
                } else {
                    while (current_op != '(' && peek_op != ',' && compare(std::string(1, current_op), std::string(1, peek_op))) {
                        postfix_stack.push_back(std::string(1, op_stack.back()));
                        op_stack.pop_back();
                        peek_op = op_stack.back();
                    }
                    op_stack.push_back(current_op);
                }
                count = 0;
                current_index = i + 1;
            } else {
                ++count;
            }
        }

        if (count > 1 || (count == 1 && !is_operator(std::string(1, arr[current_index])))) {
            postfix_stack.push_back(std::string(arr.begin() + current_index, arr.begin() + current_index + count));
        }

        while (op_stack.back() != ',') {
            postfix_stack.push_back(std::string(1, op_stack.back()));
            op_stack.pop_back();
        }

        // Return the expression unchanged (used in calculate for consistency)
        return expression;
    }

    static bool is_operator(const std::string& c) {
        if (c.length() != 1) return false;
        char ch = c[0];
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '%';
    }

    bool compare(const std::string& cur, const std::string& peek) {
        std::string cur_op = cur, peek_op = peek;
        if (cur_op == "%") cur_op = "/";
        if (peek_op == "%") peek_op = "/";
        if (cur_op.length() != 1 || peek_op.length() != 1) return false;
        int cur_idx = cur_op[0] - 40;
        int peek_idx = peek_op[0] - 40;
        if (cur_idx < 0 || cur_idx >= 8 || peek_idx < 0 || peek_idx >= 8) return false;
        return operat_priority[peek_idx] >= operat_priority[cur_idx];
    }

    static double _calculate(const std::string& first_value, const std::string& second_value, const std::string& current_op) {
        double a = std::stod(first_value);
        double b = std::stod(second_value);
        if (current_op == "+") return a + b;
        if (current_op == "-") return a - b;
        if (current_op == "*") return a * b;
        if (current_op == "/") {
            if (b == 0.0) throw std::runtime_error("Division by zero");
            return a / b;
        }
        if (current_op == "%") {
            if (b == 0.0) throw std::runtime_error("Modulo by zero");
            return std::fmod(a, b);
        }
        throw std::invalid_argument("Unexpected operator: " + current_op);
    }

    static std::string transform(const std::string& expression) {
        // Remove whitespace and trailing '='
        std::string s = expression;
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        if (!s.empty() && s.back() == '=') s.pop_back();

        std::vector<char> arr(s.begin(), s.end());
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == '-') {
                if (i == 0) {
                    arr[i] = '~';
                } else {
                    char prev = arr[i-1];
                    if (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '(' || prev == 'E' || prev == 'e') {
                        arr[i] = '~';
                    }
                }
            }
        }

        // Special case: leading '~' followed by '(' -> replace with "0-..."
        if (arr.size() > 1 && arr[0] == '~' && arr[1] == '(') {
            arr[0] = '-';
            return "0" + std::string(arr.begin(), arr.end());
        }
        return std::string(arr.begin(), arr.end());
    }

private:
    std::deque<std::string> postfix_stack;
    std::array<int, 8> operat_priority;
};