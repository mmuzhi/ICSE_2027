#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <functional>

class TwentyFourPointGame {
private:
    std::vector<int> nums;

    void generateNumbers() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 9);
        nums.resize(4);
        for (int i = 0; i < 4; i++) {
            nums[i] = dis(gen);
        }
    }

public:
    TwentyFourPointGame() {
        generateNumbers();
    }

    bool answer(const std::string& expression) {
        if (expression == "pass") {
            generateNumbers();
            return false;
        }

        std::array<int, 10> counts = {0};
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

        for (int i = 0; i < 10; i++) {
            if (counts[i] != 0) {
                return false;
            }
        }

        try {
            struct State {
                int pos;
                int ch;
                std::string expr;
            };

            State state;
            state.expr = expression;
            state.pos = -1;
            state.ch = 0;

            auto nextChar = [&state]() {
                if (state.pos < state.expr.length()) {
                    state.ch = state.expr[state.pos];
                    state.pos++;
                } else {
                    state.ch = -1;
                }
            };

            auto eat = [&](int charToEat) -> bool {
                while (state.ch == ' ') {
                    nextChar();
                }
                if (state.ch == charToEat) {
                    nextChar();
                    return true;
                }
                return false;
            };

            auto parseFactor = [&state, &eat, &nextChar, &parseTerm](double x = 0.0) -> double {
                if (eat('+')) {
                    return parseFactor();
                }
                if (eat('-')) {
                    return -parseFactor();
                }
                double result;
                int startPos = state.pos;
                if (eat('(')) {
                    result = parseTerm();
                    eat(')');
                } else if (std::isdigit(state.ch) || state.ch == '.') {
                    while (std::isdigit(state.ch) || state.ch == '.') {
                        nextChar();
                    }
                    std::string sub = state.expr.substr(startPos, state.pos - startPos);
                    result = std::stod(sub);
                } else {
                    throw std::runtime_error("Unexpected character");
                }
                return result;
            };

            auto parseTerm = [&state, &eat, &nextChar, &parseFactor](double x = 0.0) -> double {
                double result = parseFactor();
                while (true) {
                    if (eat('*')) {
                        result *= parseFactor();
                    } else if (eat('/')) {
                        result /= parseFactor();
                    } else {
                        return result;
                    }
                }
            };

            auto parseExpression = [&state, &eat, &nextChar, &parseTerm](double x = 0.0) -> double {
                double result = parseTerm();
                while (true) {
                    if (eat('+')) {
                        result += parseTerm();
                    } else if (eat('-')) {
                        result -= parseTerm();
                    } else {
                        return result;
                    }
                }
            };

            nextChar();
            double result = parseExpression();
            if (state.pos < state.expr.length()) {
                throw std::runtime_error("Unexpected characters at the end");
            }

            return result == 24;
        } catch (...) {
            return false;
        }
    }

    std::vector<int> getNums() {
        return nums;
    }
};