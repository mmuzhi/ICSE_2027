#include <string>
#include <vector>
#include <stdexcept>

class BalancedBrackets {
public:
    std::vector<char> stack;
    std::vector<char> left_brackets;
    std::vector<char> right_brackets;
    std::string expr;

    BalancedBrackets(std::string expr)
        : left_brackets{'(', '{', '['},
          right_brackets{')', '}', ']'},
          expr(std::move(expr)) {}

    void clear_expr() {
        std::string filtered;
        for (char c : this->expr) {
            bool is_bracket = false;
            for (char lb : this->left_brackets) {
                if (c == lb) { is_bracket = true; break; }
            }
            if (!is_bracket) {
                for (char rb : this->right_brackets) {
                    if (c == rb) { is_bracket = true; break; }
                }
            }
            if (is_bracket) filtered += c;
        }
        this->expr = filtered;
    }

    bool check_balanced_brackets() {
        this->clear_expr();
        for (char Brkt : this->expr) {
            bool is_left = false;
            for (char lb : this->left_brackets) {
                if (Brkt == lb) { is_left = true; break; }
            }
            if (is_left) {
                this->stack.push_back(Brkt);
            } else {
                if (this->stack.empty()) {
                    throw std::out_of_range("pop from empty list");
                }
                char Current_Brkt = this->stack.back();
                this->stack.pop_back();
                if (Current_Brkt == '(') {
                    if (Brkt != ')') return false;
                }
                if (Current_Brkt == '{') {
                    if (Brkt != '}') return false;
                }
                if (Current_Brkt == '[') {
                    if (Brkt != ']') return false;
                }
            }
        }
        if (!this->stack.empty()) return false;
        return true;
    }
};