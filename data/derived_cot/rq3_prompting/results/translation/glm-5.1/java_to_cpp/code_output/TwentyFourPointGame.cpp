#include <vector>
#include <string>
#include <random>
#include <cctype>
#include <stdexcept>

class TwentyFourPointGame {
private:
    std::vector<int> nums;
    std::mt19937 rng{std::random_device{}()};

    std::vector<int> getMyCards() {
        std::vector<int> cards;
        std::uniform_int_distribution<int> dist(1, 9);
        for (int i = 0; i < 4; i++) {
            cards.push_back(dist(rng));
        }
        return cards;
    }

public:
    TwentyFourPointGame() {
        nums = getMyCards();
    }

    bool answer(const std::string& expression) {
        if (expression == "pass") {
            nums = getMyCards();
            return false;
        }

        int counts[10] = {};
        for (char c : expression) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
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

        for (int count : counts) {
            if (count != 0) {
                return false;
            }
        }

        return evaluateExpression(expression);
    }

    bool evaluateExpression(const std::string& expression) {
        try {
            struct Parser {
                const std::string& expr;
                int pos = -1;
                int ch = 0;

                Parser(const std::string& e) : expr(e) {}

                void nextChar() {
                    ch = (++pos < static_cast<int>(expr.size())) ? expr[pos] : -1;
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
                    if (pos < static_cast<int>(expr.size())) throw std::runtime_error("Unexpected");
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
                    int startPos = this->pos;
                    if (eat('(')) {
                        x = parseExpression();
                        eat(')');
                    } else if ((ch >= '0' && ch <= '9') || ch == '.') {
                        while ((ch >= '0' && ch <= '9') || ch == '.') nextChar();
                        x = std::stod(expr.substr(startPos, this->pos - startPos));
                    } else {
                        throw std::runtime_error("Unexpected");
                    }

                    return x;
                }
            };

            Parser parser(expression);
            return parser.parse() == 24;
        } catch (...) {
            return false;
        }
    }

    std::vector<int> getNums() {
        return nums;
    }
};