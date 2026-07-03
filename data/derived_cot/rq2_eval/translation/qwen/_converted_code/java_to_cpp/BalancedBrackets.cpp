#include <iostream>
#include <stack>
#include <string>

class BalancedBrackets {
private:
    std::stack<char> stack;
    std::string leftBrackets;
    std::string rightBrackets;
    std::string expr;

public:
    BalancedBrackets(const std::string& expr) : expr(expr) {
        leftBrackets = "({[";
        rightBrackets = ")}]";
    }

    void clearExpr() {
        std::string cleanedExpr;
        for (char c : expr) {
            if (leftBrackets.find(c) != std::string::npos || rightBrackets.find(c) != std::string::npos) {
                cleanedExpr += c;
            }
        }
        expr = cleanedExpr;
    }

    bool check_balanced_brackets() {
        clearExpr();
        for (char Brkt : expr) {
            if (leftBrackets.find(Brkt) != std::string::npos) {
                stack.push(Brkt);
            } else {
                if (stack.empty()) {
                    return false;
                }
                char top = stack.top();
                stack.pop();
                if ((Brkt == ')' && top != '('') ||
                    (Brkt == '}' && top != '{') ||
                    (Brkt == ']' && top != '[')) {
                    return false;
                }
            }
        }
        return stack.empty();
    }

    std::string getExpr() const {
        return expr;
    }

    static void main(int argc, char* argv[]) {
        BalancedBrackets b("a(b)c");
        std::cout << (b.check_balanced_brackets() ? "true" : "false") << std::endl;
    }
};

int main(int argc, char* argv[]) {
    BalancedBrackets::main(argc, argv);
    return 0;
}