#include <string>
#include <vector>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

public:
    BoyerMooreSearch(const std::string& text, const std::string& pattern)
        : text(text), pattern(pattern), textLen(text.length()), patLen(pattern.length()) {}

    int match_in_pattern(char ch) {
        for (int i = patLen - 1; i >= 0; --i) {
            if (pattern[i] == ch) {
                return i;
            }
        }
        return -1;
    }

    int mismatch_in_text(int currentPos) {
        for (int i = patLen - 1; i >= 0; --i) {
            if (pattern[i] != text[currentPos + i]) {
                return currentPos + i;
            }
        }
        return -1;
    }

    std::vector<int> bad_character_heuristic() {
        std::vector<int> positions;
        int n = textLen - patLen + 1;
        int i = 0;
        while (i < n) {
            int next_i = i + 1;  // preserve sequential iteration (as in Python for loop)
            int mismatch_index = mismatch_in_text(i);
            if (mismatch_index == -1) {
                positions.push_back(i);
            } else {
                int match_index = match_in_pattern(text[mismatch_index]);
                i = mismatch_index - match_index;  // assignment is ignored for loop control
            }
            i = next_i;  // restore to next sequential index
        }
        return positions;
    }
};