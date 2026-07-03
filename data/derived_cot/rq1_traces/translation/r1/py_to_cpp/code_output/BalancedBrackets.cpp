#include <vector>
#include <string>
#include <stdexcept>

class BalancedBrackets {
public:
    std::vector<char> stack;
    std::string left_brackets;
    std::string right_brackets;
    std::string expr;

    BalancedBrackets(std::string expr) : expr(expr) {
        left_brackets = "({[";
        right_brackets = ")}]";
    }

    void clear_expr() {
        std::string cleaned;
        for (char c : expr) {
            if (left_brackets.find(c) != std::string::npos || 
                right_brackets.find(c) != std::string::npos) {
                cleaned += c;
            }
        }
        expr = cleaned;
    }

    bool check_balanced_brackets() {
        clear_expr();

        for (char Brkt : expr) {
            if (left_brackets.find(Brkt) != std::string::npos) {
                stack.push_back(Brkt);
            } else {
                if (stack.empty()) {
                    throw std::out_of_range("pop from empty stack");
                }
                char Current_Brkt = stack.back();
                stack.pop_back();

                if (Current_Brkt == '(') {
                    if (Brkt != ')') {
                        return false;
                    }
                }
                if (Current_Brkt == '{') {
                    if (Brkt != '}') {
                        return false;
                    }
                }
                if (Current_Brkt == '[') {
                    if (Brkt != ']') {
                        return false;
                    }
                }
            }
        }

        if (!stack.empty()) {
            return false;
        }
        return true;
    }
};