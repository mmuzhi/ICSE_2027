#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BalancedBrackets {
private:
    std::vector<char> stack;
    std::vector<char> left_brackets;
    std::vector<char> right_brackets;
    std::string expr;

public:
    BalancedBrackets(const std::string& expr)
        : left_brackets {'(', '{', '['},
          right_brackets {')', '}', ']'},
          expr(expr) {}

    void clear_expr() {
        std::string filtered;
        for (char c : expr) {
            if (std::find(left_brackets.begin(), left_brackets.end(), c) != left_brackets.end() ||
                std::find(right_brackets.begin(), right_brackets.end(), c) != right_brackets.end()) {
                filtered.push_back(c);
            }
        }
        expr = std::move(filtered);
    }

    bool check_balanced_brackets() {
        clear_expr();
        for (char brkt : expr) {
            if (std::find(left_brackets.begin(), left_brackets.end(), brkt) != left_brackets.end()) {
                stack.push_back(brkt);
            } else {
                if (stack.empty()) {
                    throw std::out_of_range("pop from empty stack");
                }
                char current_brkt = stack.back();
                stack.pop_back();
                if (current_brkt == '(' && brkt != ')')
                    return false;
                if (current_brkt == '{' && brkt != '}')
                    return false;
                if (current_brkt == '[' && brkt != ']')
                    return false;
            }
        }
        return stack.empty();
    }
};