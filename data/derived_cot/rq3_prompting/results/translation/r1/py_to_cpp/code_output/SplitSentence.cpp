#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include <sstream>
#include <iostream>

class SplitSentence {
public:
    std::vector<std::string> split_sentences(const std::string& sentences_string) {
        std::vector<std::string> sentences;
        std::size_t start = 0;
        const std::size_t n = sentences_string.size();

        for (std::size_t i = 0; i + 1 < n; ++i) {
            // Check for '.' or '?' followed by a single space.
            if ((sentences_string[i] == '.' || sentences_string[i] == '?') && sentences_string[i + 1] == ' ') {
                // Negative lookbehind 2: (?<![A-Z][a-z]\.)
                bool do_split = true;

                if (sentences_string[i] == '.' && i >= 2) {
                    if (std::isupper(static_cast<unsigned char>(sentences_string[i - 2])) &&
                        std::islower(static_cast<unsigned char>(sentences_string[i - 1]))) {
                        do_split = false;
                    }
                }

                // Negative lookbehind 1: (?<!\w\.\w.)
                if (do_split && i >= 3) {
                    if (std::isalnum(static_cast<unsigned char>(sentences_string[i - 3])) &&
                        sentences_string[i - 2] == '.' &&
                        std::isalnum(static_cast<unsigned char>(sentences_string[i - 1]))) {
                        do_split = false;
                    }
                }

                if (do_split) {
                    sentences.push_back(sentences_string.substr(start, i - start + 1));
                    start = i + 2; // skip the punctuation and the space
                }
            }
        }

        // Add remaining part after last split (or whole string if no split)
        if (start <= n) {
            sentences.push_back(sentences_string.substr(start));
        }

        return sentences;
    }

    int count_words(const std::string& sentence) {
        // Remove all characters that are not letters or spaces
        std::regex non_alpha("[^a-zA-Z\\s]");
        std::string cleaned = std::regex_replace(sentence, non_alpha, "");

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
        for (const auto& s : sentences) {
            int cnt = count_words(s);
            if (cnt > max_count) {
                max_count = cnt;
            }
        }
        return max_count;
    }
};

// For testing – main() is not required but shown for completeness.
// int main() {
//     SplitSentence ss;
//     std::string t = "aaa aaaa. bb bbbb bbb? cccc cccc. dd ddd?";
//     auto sents = ss.split_sentences(t);
//     for (const auto& s : sents) std::cout << "'" << s << "'\n";
//     std::cout << ss.count_words("abc def") << "\n";
//     std::cout << ss.process_text_file("aaa aaaa. bb bbbb bbb? cccc ccccccc cc ccc. dd ddd?") << "\n";
//     return 0;
// }