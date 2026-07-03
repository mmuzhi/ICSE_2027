#include <vector>
#include <string>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

    int match_in_pattern(char c) {
        for (int i = patLen - 1; i >= 0; i--) {
            if (c == pattern[i]) {
                return i;
            }
        }
        return -1;
    }

    int mismatch_in_text(int currentPos) {
        for (int i = patLen - 1; i >= 0; i--) {
            if (pattern[i] != text[currentPos + i]) {
                return currentPos + i;
            }
        }
        return -1;
    }

public:
    BoyerMooreSearch(const std::string& text, const std::string& pattern)
        : text(text), pattern(pattern), textLen(text.length()), patLen(pattern.length()) {}

    std::vector<int> bad_character_heuristic() {
        std::vector<int> positions;
        for (int i = 0; i <= textLen - patLen; i++) {
            int mismatch_index = mismatch_in_text(i);
            if (mismatch_index == -1) {
                positions.push_back(i);
            } else {
                int match_index = match_in_pattern(text[mismatch_index]);
                i = mismatch_index - match_index;
            }
        }
        return positions;
    }
};