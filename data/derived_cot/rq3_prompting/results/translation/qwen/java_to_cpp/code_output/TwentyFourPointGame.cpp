#include <vector>
#include <random>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>

class ExpressionParser {
private:
    std::string expression;
    size_t pos;
    int ch;

    void nextChar() {
        if (pos < expression.length()) {
            ch = expression[pos];
            ++pos;
        } else {
            ch = -1;
        }
    }

    bool eat(char expected) {
        while (ch == ' ') nextChar();
        if (ch == expected) {
            nextChar();
            return true;
        }
        return false;
    }

    double parseFactor() {
        if (eat('+')) {
            return parseFactor();
        }
        if (eat('-')) {
            return -parseFactor();
        }

        double x;
        if (eat('(')) {
            x = parseExpression();
            eat(')');
        } else if (std::isdigit(ch)) {
            size_t startPos = pos;
            while (std::isdigit(ch) || ch == '.') {
                nextChar();
            }
            x = std::stod(expression.substr(startPos, pos - startPos - (ch == '.' ? 0 : 0)));
        } else {
            throw std::runtime_error("Unexpected character: " + std::string(1, ch));
        }
        return x;
    }

    double parseTerm() {
        double x = parseFactor();
        for (;;) {
            if (eat('*')) {
                x *= parseFactor();
            } else if (eat('/')) {
                if (parseFactor() == 0) {
                    throw std::runtime_error("Division by zero");
                }
                x /= parseFactor();
            } else {
                return x;
            }
        }
    }

    double parseExpression() {
        double x = parseTerm();
        for (;;) {
            if (eat('+')) {
                x += parseTerm();
            } else if (eat('-')) {
                x -= parseTerm();
            } else {
                return x;
            }
        }
    }

public:
    explicit ExpressionParser(const std::string& expr) : expression(expr), pos(0), ch(0) {
        nextChar();
    }

    double parse() {
        double result = parseExpression();
        if (pos < expression.length()) {
            throw std::runtime_error("Unexpected characters at the end");
        }
        return result;
    }
};

class TwentyFourPointGame {
private:
    std::vector<int> nums;

    std::vector<int> getMyCards() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(1, 9);

        std::vector<int> cards;
        for (int i = 0; i < 4; ++i) {
            cards.push_back(distrib(gen));
        }
        return cards;
    }

public:
    TwentyFourPointGame() : nums(getMyCards()) {}

    bool answer(const std::string& expression) {
        if (expression == "pass") {
            nums = getMyCards();
            return false;
        }

        std::vector<int> counts(10, 0);
        for (char c : expression) {
            if (std::isdigit(c)) {
                int digit = c - '0';
                counts[digit]++;
            }
        }

        for (int num : nums) {
            if (counts[num] > 0) {
                counts[num]--;
            } else {
                return false;
            }
        }

        for (int count : counts) {
            if (count != 0) {
                return false;
            }
        }

        return evaluateExpression(expression);
    }

    bool evaluateExpression(const std::string& expression) {
        try {
            ExpressionParser parser(expression);
            double result = parser.parse();
            return result == 24.0;
        } catch (...) {
            return false;
        }
    }

    std::vector<int> getNums() const {
        return nums;
    }
};