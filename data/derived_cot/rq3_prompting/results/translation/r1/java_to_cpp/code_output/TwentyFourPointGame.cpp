#include <vector>
#include <string>
#include <random>
#include <cctype>
#include <stdexcept>
#include <algorithm>

class TwentyFourPointGame {
private:
    std::vector<int> nums;

    std::vector<int> getMyCards() {
        std::vector<int> cards;
        // Use a static random engine seeded once for simplicity.
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 9);
        for (int i = 0; i < 4; ++i) {
            cards.push_back(dist(rng));
        }
        return cards;
    }

    bool evaluateExpression(const std::string& expression) {
        try {
            struct Parser {
                const std::string& expr;
                int pos = -1;
                int ch = 0;

                void nextChar() {
                    ch = (++pos < static_cast<int>(expr.length())) ? expr[pos] : -1;
                }

                bool eat(int charToEat) {
                    while (ch == ' ') nextChar();
                    if (ch == charToEat) {
                        nextChar();
                        return true;
                    }
                    return false;
                }

                double parse() {
                    nextChar();
                    double x = parseExpression();
                    if (pos < static_cast<int>(expr.length()))
                        throw std::runtime_error("Unexpected: " + std::string(1, static_cast<char>(ch)));
                    return x;
                }

                double parseExpression() {
                    double x = parseTerm();
                    for (;;) {
                        if (eat('+')) x += parseTerm();
                        else if (eat('-')) x -= parseTerm();
                        else return x;
                    }
                }

                double parseTerm() {
                    double x = parseFactor();
                    for (;;) {
                        if (eat('*')) x *= parseFactor();
                        else if (eat('/')) x /= parseFactor();
                        else return x;
                    }
                }

                double parseFactor() {
                    if (eat('+')) return parseFactor();
                    if (eat('-')) return -parseFactor();

                    double x;
                    int startPos = pos;
                    if (eat('(')) {
                        x = parseExpression();
                        eat(')');
                    } else if ((ch >= '0' && ch <= '9') || ch == '.') {
                        while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
                        x = std::stod(expr.substr(startPos, pos - startPos));
                    } else {
                        throw std::runtime_error("Unexpected: " + std::string(1, static_cast<char>(ch)));
                    }
                    return x;
                }
            };

            Parser parser{expression};
            return parser.parse() == 24.0;
        } catch (...) {
            return false;
        }
    }

public:
    TwentyFourPointGame() : nums(getMyCards()) {}

    bool answer(const std::string& expression) {
        if (expression == "pass") {
            nums = getMyCards();
            return false;
        }

        int counts[10] = {0};
        for (char c : expression) {
            if (std::isdigit(c)) {
                counts[c - '0']++;
            }
        }

        for (int num : nums) {
            if (counts[num] > 0) {
                counts[num]--;
            } else {
                return false;
            }
        }

        for (int i = 0; i < 10; ++i) {
            if (counts[i] != 0) {
                return false;
            }
        }

        return evaluateExpression(expression);
    }

    std::vector<int> getNums() const {
        return nums;
    }
};