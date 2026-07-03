#include <string>
#include <vector>
#include <deque>
#include <regex>
#include <stdexcept>
#include <cmath>
#include <algorithm>

class ExpressionCalculator {
public:
    std::deque<std::string> postfix_stack;
    std::vector<int> operat_priority;

    ExpressionCalculator() {
        operat_priority = {0, 3, 2, 1, -1, 1, 0, 2};
    }

    double calculate(const std::string& expression) {
        prepare(transform(expression));

        std::deque<std::string> result_stack;
        std::reverse(postfix_stack.begin(), postfix_stack.end());

        while (!postfix_stack.empty()) {
            std::string current_op = postfix_stack.back();
            postfix_stack.pop_back();
            if (!is_operator(current_op[0])) {
                for (char& c : current_op) {
                    if (c == '~') c = '-';
                }
                result_stack.push_back(current_op);
            } else {
                std::string second_value = result_stack.back();
                result_stack.pop_back();
                std::string first_value = result_stack.back();
                result_stack.pop_back();

                for (char& c : first_value) {
                    if (c == '~') c = '-';
                }
                for (char& c : second_value) {
                    if (c == '~') c = '-';
                }

                double temp_result = _calculate(first_value, second_value, current_op);
                result_stack.push_back(std::to_string(temp_result));
            }
        }

        double final_result = 1.0;
        for (const auto& s : result_stack) {
            final_result *= std::stod(s);
        }
        return final_result;
    }

    void prepare(const std::string& expression) {
        postfix_stack.clear();
        std::deque<char> op_stack;
        op_stack.push_back(',');

        std::string arr = expression;
        int current_index = 0;
        int count = 0;

        for (int i = 0; i < (int)arr.size(); ++i) {
            char current_op = arr[i];
            if (is_operator(current_op)) {
                if (count > 0) {
                    postfix_stack.push_back(arr.substr(current_index, count));
                }
                char peek_op = op_stack.back();
                if (current_op == ')') {
                    while (op_stack.back() != '(') {
                        postfix_stack.push_back(std::string(1, op_stack.back()));
                        op_stack.pop_back();
                    }
                    op_stack.pop_back();
                } else {
                    while (current_op != '(' && peek_op != ',' && compare(current_op, peek_op)) {
                        postfix_stack.push_back(std::string(1, op_stack.back()));
                        op_stack.pop_back();
                        peek_op = op_stack.back();
                    }
                    op_stack.push_back(current_op);
                }

                count = 0;
                current_index = i + 1;
            } else {
                count += 1;
            }
        }

        if (count > 1 || (count == 1 && !is_operator(arr[current_index]))) {
            postfix_stack.push_back(arr.substr(current_index, count));
        }

        while (op_stack.back() != ',') {
            postfix_stack.push_back(std::string(1, op_stack.back()));
            op_stack.pop_back();
        }
    }

    static bool is_operator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '%';
    }

    bool compare(char cur, char peek) {
        if (cur == '%') cur = '/';
        if (peek == '%') peek = '/';
        return operat_priority[(int)peek - 40] >= operat_priority[(int)cur - 40];
    }

    static double _calculate(const std::string& first_value, const std::string& second_value, const std::string& current_op) {
        double first = std::stod(first_value);
        double second = std::stod(second_value);
        if (current_op == "+") {
            return first + second;
        } else if (current_op == "-") {
            return first - second;
        } else if (current_op == "*") {
            return first * second;
        } else if (current_op == "/") {
            return first / second;
        } else if (current_op == "%") {
            // Replicating Python's Decimal modulo behavior
            return first - second * std::floor(first / second);
        } else {
            throw std::invalid_argument("Unexpected operator: " + current_op);
        }
    }

    static std::string transform(const std::string& expression) {
        std::string expr = std::regex_replace(expression, std::regex("\\s+"), "");
        expr = std::regex_replace(expr, std::regex("=$"), "");
        
        std::string arr = expr;
        for (int i = 0; i < (int)arr.size(); ++i) {
            if (arr[i] == '-') {
                if (i == 0) {
                    arr[i] = '~';
                } else {
                    char prev_c = arr[i - 1];
                    if (prev_c == '+' || prev_c == '-' || prev_c == '*' || prev_c == '/' || prev_c == '(' || prev_c == 'E' || prev_c == 'e') {
                        arr[i] = '~';
                    }
                }
            }
        }

        if (!arr.empty() && arr[0] == '~' && arr.size() > 1 && arr[1] == '(') {
            arr[0] = '-';
            return "0" + arr;
        } else {
            return arr;
        }
    }
};