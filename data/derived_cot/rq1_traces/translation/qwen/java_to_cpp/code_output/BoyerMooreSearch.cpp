#include <vector>
#include <map>
#include <string>
#include <algorithm>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

    int matchInPattern(char ch) {
        if (patLen == 0) {
            return -1;
        }
        for (int i = patLen - 1; i >= 0; i--) {
            if (pattern[i] == ch) {
                return i;
            }
        }
        return -1;
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
    BoyerMooreSearch(const std::string& text, const std::string& pattern) 
        : text(text), pattern(pattern), textLen(text.length()), patLen(pattern.length()) {}

    std::vector<int> badCharacterHeuristic() {
        std::vector<int> positions;

        if (patLen == 0) {
            for (int j = 0; j <= textLen; j++) {
                positions.push_back(j);
            }
            return positions;
        }

        std::map<char, int> badCharHeuristic;
        for (int j = 0; j < patLen; j++) {
            badCharHeuristic[pattern[j]] = j;
        }

        int i = 0;

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
                    i += std::max(1, mismatchIndex - i - matchIndex);
                } else {
                    i += (mismatchIndex - i + 1);
                }
            }
        }

        return positions;
    }
};