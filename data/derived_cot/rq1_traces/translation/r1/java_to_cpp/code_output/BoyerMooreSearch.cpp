#include <vector>
#include <string>
#include <unordered_map>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

public:
    BoyerMooreSearch(const std::string& text, const std::string& pattern)
        : text(text), pattern(pattern), textLen(text.length()), patLen(pattern.length()) {}

private:
    int matchInPattern(char ch) {
        size_t pos = pattern.rfind(ch);
        if (pos == std::string::npos) {
            return -1;
        }
        return static_cast<int>(pos);
    }

    int mismatchInText(int currentPos) {
        for (int j = patLen - 1; j >= 0; j--) {
            if (pattern[j] != text[currentPos + j]) {
                return currentPos + j;
            }
        }
        return -1;
    }

public:
    std::vector<int> badCharacterHeuristic() {
        std::vector<int> positions;
        int i = 0;

        if (patLen == 0) {
            for (int j = 0; j <= textLen; j++) {
                positions.push_back(j);
            }
            return positions;
        }

        std::unordered_map<char, int> badCharHeuristic;
        for (int j = 0; j < patLen; j++) {
            badCharHeuristic[pattern[j]] = j;
        }

        while (i <= textLen - patLen) {
            int mismatchIndex = mismatchInText(i);
            if (mismatchIndex == -1) {
                positions.push_back(i);
                i += patLen;
            } else {
                char mismatchChar = text[mismatchIndex];
                auto it = badCharHeuristic.find(mismatchChar);
                int matchIndex = (it != badCharHeuristic.end()) ? it->second : -1;

                if (matchIndex >= 0) {
                    int j = mismatchIndex - i;
                    int shift = j - matchIndex;
                    if (shift <= 0) {
                        i++;
                    } else {
                        i += shift;
                    }
                } else {
                    i += (mismatchIndex - i) + 1;
                }
            }
        }
        return positions;
    }
};