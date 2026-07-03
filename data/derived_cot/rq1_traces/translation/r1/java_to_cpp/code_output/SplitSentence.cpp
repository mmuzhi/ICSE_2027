#include <vector>
#include <string>
#include <sstream>
#include <cctype>

class SplitSentence {
public:
    std::vector<std::string> splitSentences(const std::string& s);
    int countWords(const std::string& sentence);
    int processTextFile(const std::string& sentencesString);

private:
    bool isWordChar(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_');
    }
    bool isUpperCase(char c) {
        return (c >= 'A' && c <= 'Z');
    }
    bool isLowerCase(char c) {
        return (c >= 'a' && c <= 'z');
    }
};

std::vector<std::string> SplitSentence::splitSentences(const std::string& s) {
    std::vector<std::string> sentences;
    if (s.empty()) {
        return sentences;
    }
    int lastEnd = 0;
    int len = s.length();

    for (int i = 0; i < len - 1; i++) {
        if (s[i] == '.' || s[i] == '?') {
            if (std::isspace(static_cast<unsigned char>(s[i+1]))) {
                bool skip = false;
                if (s[i] == '.') {
                    if (i - 3 >= 0) {
                        if (isWordChar(s[i-3]) && s[i-2] == '.' && isWordChar(s[i-1]) && s[i] == '.') {
                            skip = true;
                        }
                    }
                    if (!skip && i - 2 >= 0) {
                        if (isUpperCase(s[i-2]) && isLowerCase(s[i-1]) && s[i] == '.') {
                            skip = true;
                        }
                    }
                }
                if (!skip) {
                    sentences.push_back(s.substr(lastEnd, i - lastEnd + 1));
                    lastEnd = i + 2;
                }
            }
        }
    }

    if (lastEnd < len) {
        sentences.push_back(s.substr(lastEnd));
    }

    return sentences;
}

int SplitSentence::countWords(const std::string& sentence) {
    std::string cleaned;
    for (char c : sentence) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || std::isspace(static_cast<unsigned char>(c))) {
            cleaned += c;
        }
    }

    std::istringstream iss(cleaned);
    std::string word;
    int count = 0;
    while (iss >> word) {
        count++;
    }
    return count;
}

int SplitSentence::processTextFile(const std::string& sentencesString) {
    auto sentences = splitSentences(sentencesString);
    int maxCount = 0;
    for (const auto& sentence : sentences) {
        int cnt = countWords(sentence);
        if (cnt > maxCount) {
            maxCount = cnt;
        }
    }
    return maxCount;
}