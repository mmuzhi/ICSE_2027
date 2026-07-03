#include <stack>
#include <vector>
#include <string>

class BalancedBrackets {
private:
    std::string expr;
    std::stack<char> stack;
    std::vector<char> left_brackets;
    std::vector<char> right_brackets;

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
            if (std::find(left_brackets.begin(), left_brackets.end(), Brkt) != left_brackets.end()) {
                stack.push(Brkt);
            } else {
                if (stack.empty()) {
                    return false;
                }
                char Current_Brkt = stack.top();
                stack.pop();
                if (Current_Brkt == '(' && Brkt != ')') return false;
                if (Current_Brkt == '{' && Brkt != '}') return false;
                if (Current_Brkt == '[' && Brkt != ']') return false;
            }
        }
        return stack.empty();
    }
};