#include <vector>
#include <string>

using namespace std;

class BoyerMooreSearch {
    string text;
    string pattern;
    int textLen;
    int patLen;

public:
    BoyerMooreSearch(string text, string pattern) : 
        text(text), pattern(pattern), 
        textLen(text.length()), patLen(pattern.length()) 
    {}

    int match_in_pattern(char c) {
        for (int i = patLen - 1; i >= 0; i--) {
            if (pattern[i] == c) {
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

    vector<int> bad_character_heuristic() {
        vector<int> positions;
        if (patLen == 0) {
            for (int i = 0; i <= textLen; i++) {
                positions.push_back(i);
            }
            return positions;
        }
        int max_index = textLen - patLen;
        for (int i = 0; i <= max_index; i++) {
            int mismatch_index = mismatch_in_text(i);
            if (mismatch_index == -1) {
                positions.push_back(i);
            } else {
                char c = text[mismatch_index];
                int match_index = match_in_pattern(c);
                int dummy = mismatch_index - match_index;
            }
        }
        return positions;
    }
};