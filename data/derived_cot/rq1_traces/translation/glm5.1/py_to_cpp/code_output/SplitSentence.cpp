#include <cctype>
#include <sstream>
#include <string>
#include <vector>

class SplitSentence {
public:
    std::vector<std::string> split_sentences(const std::string& sentences_string) {
        std::vector<std::string> result;
        std::string current;

        for (size_t i = 0; i < sentences_string.size(); ++i) {
            char c = sentences_string[i];

            bool is_ws = (c == ' ' || c == '\t' || c == '\n' ||
                          c == '\r' || c == '\f' || c == '\v');

            if (is_ws) {
                // Positive lookbehind (?<=\.|\?): char before whitespace is '.' or '?'
                bool pos_lb = (i >= 1 &&
                               (sentences_string[i - 1] == '.' ||
                                sentences_string[i - 1] == '?'));

                // Negative lookbehind (?<!\w\.\w.): not preceded by \w\.\w.
                // \w matches [a-zA-Z0-9_], the trailing . matches any char
                bool neg_lb1 = false;
                if (i >= 4) {
                    auto is_word = [](char ch) {
                        return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_';
                    };
                    if (is_word(sentences_string[i - 4]) &&
                        sentences_string[i - 3] == '.' &&
                        is_word(sentences_string[i - 2])) {
                        neg_lb1 = true;
                    }
                }

                // Negative lookbehind (?<![A-Z][a-z]\.): not preceded by [A-Z][a-z]\.
                bool neg_lb2 = false;
                if (i >= 3) {
                    if (std::isupper(static_cast<unsigned char>(sentences_string[i - 3])) &&
                        std::islower(static_cast<unsigned char>(sentences_string[i - 2])) &&
                        sentences_string[i - 1] == '.') {
                        neg_lb2 = true;
                    }
                }

                if (pos_lb && !neg_lb1 && !neg_lb2) {
                    result.push_back(current);
                    current.clear();
                    continue; // consume the whitespace (matches re.split behavior)
                }
            }

            current += c;
        }

        result.push_back(current);
        return result;
    }

    int count_words(const std::string& sentence) {
        // Remove all characters that are not letters or whitespace
        std::string cleaned;
        for (char c : sentence) {
            if (std::isalpha(static_cast<unsigned char>(c)) ||
                c == ' ' || c == '\t' || c == '\n' ||
                c == '\r' || c == '\f' || c == '\v') {
                cleaned += c;
            }
        }

        // Split by whitespace and count
        std::istringstream iss(cleaned);
        std::string word;
        int count = 0;
        while (iss >> word) {
            ++count;
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