#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

class IndexError : public std::exception {
public:
    const char* what() const noexcept override {
        return "list index out of range";
    }
};

class BalancedBrackets {
private:
    std::stack<char> stack;
    std::vector<char> left_brackets;
    std::vector<char> right_brackets;
    std::string expr;

public:
    BalancedBrackets(const std::string& expr) : expr(expr) {
        left_brackets = {'(', '{', '['};
        right_brackets = {')', '}', ']'];
    }

    void clear_expr() {
        std::string new_expr;
        for (char c : expr) {
            if (std::find(left_brackets.begin(), left_brackets.end(), c) != left_brackets.end() ||
                std::find(right_brackets.begin(), right_brackets.end(), c) != right_brackets.end()) {
                new_expr += c;
            }
        }
        expr = new_expr;
    }

    bool check_balanced_brackets() {
        clear_expr();
        for (char Brkt : expr) {
            if (Brkt in left_brackets) {
                stack.push(Brkt);
            } else {
                if (stack.empty()) {
                    throw IndexError();
                }
                char Current_Brkt = stack.top();
                stack.pop();
                if (Current_Brkt == '(') {
                    if (Brkt != ')') return false;
                } else if (Current_Brkt == '{') {
                    if (Brkt != '}') return false;
                } else if (Current_Brkt == '[') {
                    if (Brkt != ']') return false;
                }
            }
        }
        if (!stack.empty()) return false;
        return true;
    }
};