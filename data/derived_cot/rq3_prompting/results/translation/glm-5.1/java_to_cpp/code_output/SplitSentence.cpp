#include <vector>
#include <string>
#include <cctype>

class SplitSentence {
public:
    std::vector<std::string> splitSentences(const std::string& sentencesString) {
        std::vector<std::string> sentences;
        int lastEnd = 0;
        int n = static_cast<int>(sentencesString.size());

        for (int i = 1; i < n; i++) {
            char prev = sentencesString[i - 1];
            char curr = sentencesString[i];

            if ((prev == '.' || prev == '?') && isWhitespace(curr)) {
                // Negative lookbehind: \w\.\w. (4 chars before whitespace position)
                bool negLookbehind1 = false;
                if (i >= 4) {
                    char c4 = sentencesString[i - 4];
                    char c3 = sentencesString[i - 3];
                    char c2 = sentencesString[i - 2];
                    if (isWordChar(c4) && c3 == '.' && isWordChar(c2) && prev == '.') {
                        negLookbehind1 = true;
                    }
                }

                // Negative lookbehind: [A-Z][a-z]\. (3 chars before whitespace position)
                bool negLookbehind2 = false;
                if (i >= 3 && prev == '.') {
                    char c3 = sentencesString[i - 3];
                    char c2 = sentencesString[i - 2];
                    if (std::isupper(static_cast<unsigned char>(c3)) &&
                        std::islower(static_cast<unsigned char>(c2))) {
                        negLookbehind2 = true;
                    }
                }

                if (!negLookbehind1 && !negLookbehind2) {
                    sentences.push_back(sentencesString.substr(lastEnd, i - lastEnd));
                    lastEnd = i + 1;
                }
            }
        }

        if (lastEnd < n) {
            sentences.push_back(sentencesString.substr(lastEnd));
        }

        return sentences;
    }

    int countWords(const std::string& sentence) {
        std::string cleaned;
        for (char c : sentence) {
            if (std::isalpha(static_cast<unsigned char>(c)) || isWhitespace(c)) {
                cleaned += c;
            }
        }

        std::vector<std::string> words = splitOnWhitespace(cleaned);
        return static_cast<int>(words.size());
    }

    int processTextFile(const std::string& sentencesString) {
        std::vector<std::string> sentences = splitSentences(sentencesString);
        int maxCount = 0;
        for (const std::string& sentence : sentences) {
            int count = countWords(sentence);
            if (count > maxCount) {
                maxCount = count;
            }
        }
        return maxCount;
    }

private:
    static bool isWhitespace(char c) {
        return std::isspace(static_cast<unsigned char>(c)) != 0;
    }

    static bool isWordChar(char c) {
        return std::isalnum(static_cast<unsigned char>(c)) != 0 || c == '_';
    }

    static std::vector<std::string> splitOnWhitespace(const std::string& s) {
        std::vector<std::string> result;

        if (s.empty()) {
            result.push_back("");
            return result;
        }

        size_t lastEnd = 0;
        size_t i = 0;

        while (i < s.size()) {
            if (isWhitespace(s[i])) {
                result.push_back(s.substr(lastEnd, i - lastEnd));
                while (i < s.size() && isWhitespace(s[i])) {
                    i++;
                }
                lastEnd = i;
            } else {
                i++;
            }
        }

        result.push_back(s.substr(lastEnd));

        // Java's split discards trailing empty strings
        while (!result.empty() && result.back().empty()) {
            result.pop_back();
        }

        return result;
    }
};