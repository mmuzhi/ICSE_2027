#include <vector>
#include <string>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

    int match_in_pattern(char c) {
        if (patLen == 0) {
            return -1;
        }
        for (int i = patLen - 1; i >= 0; i--) {
            if (pattern[i] == c) {
                return i;
            }
        }
        return -1;
    }

    int mismatch_in_text(int currentPos) {
        if (patLen == 0) {
            return -1;
        }
        for (int i = patLen - 1; i >= 0; i--) {
            if (pattern[i] != text[currentPos + i]) {
                return currentPos + i;
            }
        }
        return -1;
    }

public:
    BoyerMooreSearch(const std::string& text, const std::string& pattern) : 
        text(text), pattern(pattern), textLen(text.length()), patLen(pattern.length()) {}

    std::vector<int> bad_character_heuristic() {
        std::vector<int> positions;
        int i = 0;
        while (i <= textLen - patLen) {
            int mismatch_index = mismatch_in_text(i);
            if (mismatch_index == -1) {
                positions.push_back(i);
                i++;
            } else {
                int match_index = match_in_pattern(text[mismatch_index]);
                i = mismatch_index - match_index;
            }
        }
        return positions;
    }
};