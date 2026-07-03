#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <iterator>
#include <cctype>
#include <algorithm>

class SplitSentence {
public:
    std::vector<std::string> split_sentences(const std::string& sentences_string) {
        if (sentences_string.empty()) {
            return {};
        }
        std::regex split_re(R"((?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=[.?])\s)");
        std::sregex_token_iterator iter(sentences_string.begin(), sentences_string.end(), split_re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> sentences;
        for (; iter != end; ++iter) {
            sentences.push_back(*iter);
        }
        return sentences;
    }

    int count_words(const std::string& sentence) {
        std::string clean_sentence;
        for (unsigned char c : sentence) {
            if (std::isalpha(c) || std::isspace(c)) {
                clean_sentence += c;
            }
        }
        std::istringstream iss(clean_sentence);
        return std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
    }

    int process_text_file(const std::string& sentences_string) {
        auto sentences = split_sentences(sentences_string);
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