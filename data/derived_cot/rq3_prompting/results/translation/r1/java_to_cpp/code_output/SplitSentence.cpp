#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include <algorithm>
#include <iterator>

class SplitSentence {
public:
    // Splits the input string into sentences based on '.', '?' followed by whitespace,
    // but not if the punctuation is part of common abbreviations (e.g., "e.g." or "Mr.").
    std::vector<std::string> splitSentences(const std::string& sentencesString) {
        std::vector<std::string> sentences;
        std::regex sentenceEnd(R"([.?]\s)");                     // matches punctuation followed by a space
        std::regex abbr1(R"(\w\.\w.)");                          // matches e.g. "a.b.x" (word, dot, word, any)
        std::regex abbr2(R"([A-Z][a-z]\.)");                     // matches e.g. "Mr."

        auto it = std::sregex_iterator(sentencesString.begin(), sentencesString.end(), sentenceEnd);
        auto end = std::sregex_iterator();
        std::size_t lastEnd = 0;

        for (; it != end; ++it) {
            std::size_t punctPos = it->position();    // index of the punctuation character
            std::size_t afterSpace = punctPos + it->length(); // index after the space

            bool isBoundary = true;

            // Check negative lookbehind #1: (?<!\w\.\w.)
            if (punctPos >= 3) {
                std::string pre = sentencesString.substr(punctPos - 3, 4);
                if (std::regex_match(pre, abbr1)) {
                    isBoundary = false;
                }
            }
            // Check negative lookbehind #2: (?<![A-Z][a-z]\.)
            if (isBoundary && punctPos >= 2) {
                std::string pre = sentencesString.substr(punctPos - 2, 3);
                if (std::regex_match(pre, abbr2)) {
                    isBoundary = false;
                }
            }

            if (isBoundary) {
                // Substitute: include the punctuation but not the space
                sentences.push_back(sentencesString.substr(lastEnd, punctPos - lastEnd + 1));
                lastEnd = afterSpace;
            }
        }
        // Add the remaining part (if any) as the last sentence
        if (lastEnd < sentencesString.length()) {
            sentences.push_back(sentencesString.substr(lastEnd));
        }
        return sentences;
    }

    // Counts words in a sentence.
    // Behaviour: first removes all non‑letter, non‑space characters, then splits on whitespace
    // using Java's String.split() semantics (leading empty tokens kept, trailing empties removed,
    // empty string yields one empty token).
    int countWords(const std::string& sentence) {
        std::string cleaned = std::regex_replace(sentence, std::regex("[^a-zA-Z\\s]"), "");
        std::vector<std::string> tokens = splitJavaStyle(cleaned, std::regex("\\s+"));
        return static_cast<int>(tokens.size());
    }

    // Processes a text: splits into sentences and returns the maximum word count among them.
    int processTextFile(const std::string& sentencesString) {
        std::vector<std::string> sentences = splitSentences(sentencesString);
        int maxCount = 0;
        for (const auto& sentence : sentences) {
            int count = countWords(sentence);
            if (count > maxCount) {
                maxCount = count;
            }
        }
        return maxCount;
    }

private:
    // Emulates Java's String.split(regex) without limit argument.
    // Leading empty tokens are kept, trailing empty tokens are removed.
    // An empty string produces a single empty token.
    std::vector<std::string> splitJavaStyle(const std::string& s, const std::regex& delim) {
        if (s.empty()) {
            return {""};
        }
        std::vector<std::string> tokens;
        std::sregex_token_iterator iter(s.begin(), s.end(), delim, -1);
        std::sregex_token_iterator end;
        for (; iter != end; ++iter) {
            tokens.push_back(*iter);
        }
        // Remove trailing empty tokens (Java's split behaviour).
        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        return tokens;
    }
};

// Example usage (not required, but can be provided for completeness)
// int main() { ... }