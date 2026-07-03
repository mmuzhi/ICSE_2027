#include <vector>
#include <random>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cctype>
#include <cmath>

class TwentyFourPointGame {
private:
    std::vector<int> nums;

    std::vector<int> getMyCards() {
        std::vector<int> cards;
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(1, 9);
        for (int i = 0; i < 4; i++) {
            cards.push_back(uni(rng));
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

        int counts[10] = {0};

        for (char c : expression) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                int digit = c - '0';
                if (digit >= 0 && digit <= 9) {
                    counts[digit]++;
                }
            }
        }

        for (int num : nums) {
            if (counts[num] > 0) {
                counts[num]--;
            } else {
                return false;
            }
        }

        for (int i = 0; i < 10; i++) {
            if (counts[i] != 0) {
                return false;
            }
        }

        return evaluate_expression(expression);
    }

    bool evaluate_expression(const std::string& expression) {
        try {
            class ExprParser {
            private:
                const std::string& expr;
                int pos;
                int ch;

                void generate_cards() {
                    ch = (++pos < static_cast<int>(expr.size())) ? expr[pos] : -1;
                }

                bool eat(int charToEat) {
                    while (ch == ' ') generate_cards();
                    if (ch == charToEat) {
                        generate_cards();
                        return true;
                    }
                    return false;
                }

            public:
                ExprParser(const std::string& expr) : expr(expr), pos(-1), ch(0) {
                    generate_cards();
                }

                double parse() {
                    double x = parseExpression();
                    if (pos < static_cast<int>(expr.size())) {
                        throw std::runtime_error("Unexpected character");
                    }
                    return x;
                }

                double parseExpression() {
                    double x = set_nums();
                    while (true) {
                        if (eat('+')) {
                            x += set_nums();
                        } else if (eat('-')) {
                            x -= set_nums();
                        } else {
                            return x;
                        }
                    }
                }

                double set_nums() {
                    double x = parseFactor();
                    while (true) {
                        if (eat('*')) {
                            x *= parseFactor();
                        } else if (eat('/')) {
                            x /= parseFactor();
                        } else {
                            return x;
                        }
                    }
                }

                double parseFactor() {
                    if (eat('+')) return parseFactor();
                    if (eat('-')) return -parseFactor();

                    double x;
                    int startPos = pos;

                    if (eat('(')) {
                        x = parseExpression();
                        if (!eat(')')) {
                            throw std::runtime_error("Missing ')'");
                        }
                    } else if ((ch >= '0' && ch <= '9') || ch == '.') {
                        while ((ch >= '0' && ch <= '9') || ch == '.') {
                            generate_cards();
                        }
                        std::string numStr = expr.substr(startPos, pos - startPos);
                        try {
                            size_t pos;
                            x = std::stod(numStr, &pos);
                            if (pos != numStr.size()) {
                                throw std::runtime_error("Invalid number format");
                            }
                        } catch (const std::exception& e) {
                            throw std::runtime_error("Invalid number: " + numStr);
                        }
                    } else {
                        throw std::runtime_error("Unexpected character");
                    }

                    return x;
                }
            };

            ExprParser parser(expression);
            double result = parser.parse();
            return (result == 24.0);
        } catch (...) {
            return false;
        }
    }

    std::vector<int> getNums() const {
        return nums;
    }
};