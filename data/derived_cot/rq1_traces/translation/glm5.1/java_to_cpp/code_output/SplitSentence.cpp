#include <string>
#include <vector>
#include <sstream>

namespace org::example {

class SplitSentence {
public:
    std::vector<std::string> splitSentences(const std::string& sentencesString) {
        std::vector<std::string> sentences;
        size_t lastEnd = 0;
        
        for (size_t i = 1; i < sentencesString.length(); ++i) {
            unsigned char uc = sentencesString[i];
            if (is_s(uc)) {
                unsigned char prev = sentencesString[i - 1];
                if (prev == '?' || prev == '.') {
                    bool matchNeg1 = false;
                    bool matchNeg2 = false;

                    if (prev == '.') {
                        // Check (?<!\w\.\w.)
                        if (i >= 4) {
                            unsigned char c1 = sentencesString[i - 4];
                            unsigned char c2 = sentencesString[i - 3];
                            unsigned char c3 = sentencesString[i - 2];
                            unsigned char c4 = sentencesString[i - 1]; // which is '.'
                            if (is_w(c1) && c2 == '.' && is_w(c3) && c4 == '.') {
                                matchNeg1 = true;
                            }
                        }
                        // Check (?<![A-Z][a-z]\.)
                        if (i >= 3) {
                            unsigned char c1 = sentencesString[i - 3];
                            unsigned char c2 = sentencesString[i - 2];
                            unsigned char c3 = sentencesString[i - 1]; // which is '.'
                            if (is_upper_az(c1) && is_lower_az(c2) && c3 == '.') {
                                matchNeg2 = true;
                            }
                        }
                    }

                    if (!matchNeg1 && !matchNeg2) {
                        sentences.push_back(sentencesString.substr(lastEnd, i - lastEnd));
                        lastEnd = i + 1;
                    }
                }
            }
        }
        if (lastEnd < sentencesString.length()) {
            sentences.push_back(sentencesString.substr(lastEnd));
        }
        return sentences;
    }

    int countWords(const std::string& sentence) {
        std::string cleanedSentence;
        for (char c : sentence) {
            unsigned char uc = c;
            if (is_alpha_or_space(uc)) {
                cleanedSentence += c;
            }
        }
        
        // Replicates Java's specific split behavior where "".split("\\s+") returns an array of length 1
        if (cleanedSentence.empty()) {
            return 1; 
        }
        
        std::istringstream iss(cleanedSentence);
        int count = 0;
        std::string word;
        while (iss >> word) {
            count++;
        }
        return count;
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
    // Helper equivalent to Java's \w (word character: [a-zA-Z_0-9])
    static bool is_w(unsigned char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
    }

    // Helper equivalent to Java's \s (whitespace character)
    static bool is_s(unsigned char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\x0B' || c == '\f' || c == '\r';
    }

    // Helper equivalent to Java's [A-Z]
    static bool is_upper_az(unsigned char c) {
        return c >= 'A' && c <= 'Z';
    }

    // Helper equivalent to Java's [a-z]
    static bool is_lower_az(unsigned char c) {
        return c >= 'a' && c <= 'z';
    }

    // Helper equivalent to Java's [a-zA-Z\s]
    static bool is_alpha_or_space(unsigned char c) {
        return is_upper_az(c) || is_lower_az(c) || is_s(c);
    }
};

} // namespace org::example