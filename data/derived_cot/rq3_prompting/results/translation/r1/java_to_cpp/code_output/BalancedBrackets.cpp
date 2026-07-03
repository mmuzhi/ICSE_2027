#include <iostream>
#include <stack>
#include <string>

using namespace std;

class BalancedBrackets {
private:
    stack<char> stack;
    string leftBrackets;
    string rightBrackets;
    string expr;
public:
    BalancedBrackets(const string& expr) 
        : leftBrackets("({["), rightBrackets(")}]"), expr(expr) {}

    void clearExpr() {
        string cleanedExpr;
        for (char c : expr) {
            if (leftBrackets.find(c) != string::npos || 
                rightBrackets.find(c) != string::npos) {
                cleanedExpr += c;
            }
        }
        expr = cleanedExpr;
    }

    bool checkBalancedBrackets() {
        clearExpr();
        for (char Brkt : expr) {
            if (leftBrackets.find(Brkt) != string::npos) {
                stack.push(Brkt);
            } else {
                if (stack.empty()) {
                    return false;
                }
                char currentBrkt = stack.top();
                stack.pop();
                if (currentBrkt == '(' && Brkt != ')') return false;
                if (currentBrkt == '{' && Brkt != '}') return false;
                if (currentBrkt == '[' && Brkt != ']') return false;
            }
        }
        return stack.empty();
    }

    const string& getExpr() const {
        return expr;
    }
};

int main() {
    BalancedBrackets b("a(b)c");
    cout << boolalpha << b.checkBalancedBrackets() << endl;
    return 0;
}