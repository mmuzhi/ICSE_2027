#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

public:
    BoyerMooreSearch(const std::string& text, const std::string& pattern) 
        : text(text), pattern(pattern), textLen(text.length()), patLen(pattern.length()) {}

    int matchInPattern(char ch) {
        size_t pos = pattern.rfind(ch);
        if (pos == std::string::npos) {
            return -1;
        }
        return static_cast<int>(pos);
    }

    int mismatchInText(int currentPos) {
        for (int i = patLen - 1; i >= 0; i--) {
            if (pattern[i] != text[currentPos + i]) {
                return currentPos + i;
            }
        }
        return -1;
    }

    std::vector<int> badCharacterHeuristic() {
        if (pattern.empty()) {
            std::vector<int> positions;
            for (int j = 0; j <= textLen; ++j) {
                positions.push_back(j);
            }
            return positions;
        }

        std::unordered_map<char, int> badCharHeuristic;
        for (int j = 0; j < patLen; j++) {
            badCharHeuristic[pattern[j]] = j;
        }

        int i = 0;
        std::vector<int> positions;

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
                    i += mismatchIndex - i + 1;
                }
            }
        }

        return positions;
    }
};