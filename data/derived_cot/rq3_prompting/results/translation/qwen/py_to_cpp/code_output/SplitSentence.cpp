#include <regex>
#include <vector>
#include <sstream>
#include <cctype>
#include <string>

class SplitSentence {
public:
    std::vector<std::string> split_sentences(const std::string& sentences_string) {
        std::regex pattern(R"( (?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s )");
        std::sregex_token_iterator iter(sentences_string.begin(), sentences_string.end(), pattern, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> sentences;
        for (; iter != end; ++iter) {
            sentences.push_back(*iter);
        }
        return sentences;
    }

    int count_words(const std::string& sentence) {
        std::string cleaned;
        for (char c : sentence) {
            if (std::isalpha(c) || std::isspace(c)) {
                cleaned.push_back(c);
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

    int process_text_file(const std::string& sentences_string) {
        std::vector<std::string> sentences = split_sentences(sentences_string);
        int max_count = 0;
        for (const auto& sentence : sentences) {
            int count = count_words(sentence);
            if (count > max_count) {
                max_count = count;
            }
        }
        return max_count;
    }
};