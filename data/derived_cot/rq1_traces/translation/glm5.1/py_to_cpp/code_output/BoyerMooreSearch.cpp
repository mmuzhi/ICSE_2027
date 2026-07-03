#include <string>
#include <vector>

class BoyerMooreSearch {
private:
    std::string text;
    std::string pattern;
    int textLen;
    int patLen;

public:
    BoyerMooreSearch(std::string text, std::string pattern)
        : text(std::move(text)), pattern(std::move(pattern)),
          textLen(static_cast<int>(this->text.length())),
          patLen(static_cast<int>(this->pattern.length())) {}

    int match_in_pattern(char c) const {
        for (int i = patLen - 1; i >= 0; --i) {
            if (c == pattern[i]) {
                return i;
            }
        }
        return -1;
    }

    int mismatch_in_text(int currentPos) const {
        for (int i = patLen - 1; i >= 0; --i) {
            if (pattern[i] != text[currentPos + i]) {
                return currentPos + i;
            }
        }
        return -1;
    }

    std::vector<int> bad_character_heuristic() const {
        std::vector<int> positions;
        // In Python, reassigning the loop variable 'i' inside a for loop does not 
        // affect the loop's iteration sequence. To replicate this exact behavior 
        // in C++, we use 'range_i' for the loop control and assign it to 'i' 
        // so that the reassignment does not skip or repeat iterations.
        for (int range_i = 0; range_i <= textLen - patLen; ++range_i) {
            int i = range_i;
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