#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <cctype>

class SplitSentence {
public:
    std::vector<std::string> splitSentences(const std::string& sentencesString) {
        if (sentencesString.empty()) {
            return {};
        }

        std::regex pattern(R"( (?<!\w\.\w.) (?<![A-Z][a-z]\.) (?<=[\.\?])\s )");
        auto begin = std::sregex_iterator(sentencesString.begin(), sentencesString.end(), pattern);
        auto end = std::sregex_iterator();

        std::vector<std::string> sentences;
        size_t lastEnd = 0;
        for (auto i = begin; i != end; ++i) {
            std::smatch match = *i;
            sentences.push_back(sentencesString.substr(lastEnd, match.start() - lastEnd));
            lastEnd = match.end();
        }
        if (lastEnd < sentencesString.length()) {
            sentences.push_back(sentencesString.substr(lastEnd));
        }
        return sentences;
    }

    int countWords(const std::string& sentence) {
        if (sentence.empty()) {
            return 0;
        }

        std::string cleaned;
        for (char c : sentence) {
            if (std::isalnum(c) || c == ' ') {
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
};