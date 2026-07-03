#include <string>
#include <vector>

class SplitSentence {
private:
    bool is_word_char(char c) const {
        unsigned char uc = static_cast<unsigned char>(c);
        return (uc >= 'a' && uc <= 'z') || (uc >= 'A' && uc <= 'Z') || (uc >= '0' && uc <= '9') || c == '_';
    }

    bool is_upper_ascii(char c) const {
        unsigned char uc = static_cast<unsigned char>(c);
        return uc >= 'A' && uc <= 'Z';
    }

    bool is_lower_ascii(char c) const {
        unsigned char uc = static_cast<unsigned char>(c);
        return uc >= 'a' && uc <= 'z';
    }

    bool is_alpha_ascii(char c) const {
        return is_upper_ascii(c) || is_lower_ascii(c);
    }

    bool is_space_ascii(char c) const {
        unsigned char uc = static_cast<unsigned char>(c);
        return uc == ' ' || uc == '\t' || uc == '\n' || uc == '\r' || uc == '\f' || uc == '\v';
    }

public:
    std::vector<std::string> split_sentences(const std::string& sentences_string) {
        std::vector<std::string> result;
        int start = 0;
        int n = static_cast<int>(sentences_string.size());

        for (int i = 0; i < n; ++i) {
            if ((sentences_string[i] == '.' || sentences_string[i] == '?') &&
                i + 1 < n && is_space_ascii(sentences_string[i + 1])) {
                
                bool skip = false;
                // (?<![A-Z][a-z]\.)
                if (i >= 2 && is_upper_ascii(sentences_string[i - 2]) && 
                    is_lower_ascii(sentences_string[i - 1]) && 
                    sentences_string[i] == '.') {
                    skip = true;
                }
                // (?<!\w\.\w.)
                if (i >= 3 && is_word_char(sentences_string[i - 3]) && 
                    sentences_string[i - 2] == '.' && 
                    is_word_char(sentences_string[i - 1]) && 
                    sentences_string[i] == '.') {
                    skip = true;
                }
                
                if (!skip) {
                    result.push_back(sentences_string.substr(start, i - start + 1));
                    start = i + 2; // skip the space
                    i++;          // skip the space in the next iteration
                }
            }
        }
        if (start <= n) {
            result.push_back(sentences_string.substr(start));
        }
        return result;
    }

    int count_words(const std::string& sentence) {
        std::string cleaned;
        for (char c : sentence) {
            if (is_alpha_ascii(c) || is_space_ascii(c)) {
                cleaned += c;
            }
        }

        int count = 0;
        bool in_word = false;
        for (char c : cleaned) {
            if (is_space_ascii(c)) {
                in_word = false;
            } else {
                if (!in_word) {
                    count++;
                    in_word = true;
                }
            }
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