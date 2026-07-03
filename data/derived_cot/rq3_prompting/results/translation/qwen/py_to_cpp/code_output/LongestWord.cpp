#include <cctype>
#include <locale>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class LongestWord {
private:
    std::vector<std::string> word_list;

public:
    void add_word(const std::string& word) {
        word_list.push_back(word);
    }

    std::string find_longest_word(const std::string& sentence) {
        std::string longest_word = "";

        // Convert the entire sentence to lowercase
        std::string sentence_lower;
        std::locale loc;
        for (char c : sentence) {
            sentence_lower += std::tolower(c, loc);
        }

        // Define punctuation characters to remove
        std::string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        std::string sentence_no_punct;
        for (char c : sentence_lower) {
            if (punctuation.find(c) == std::string::npos) {
                sentence_no_punct += c;
            }
        }

        // Split the sentence by spaces
        std::istringstream iss(sentence_no_punct);
        std::string word;
        while (iss >> word) {
            // Check if the word exists in the word_list
            if (std::find(word_list.begin(), word_list.end(), word) != word_list.end()) {
                if (word.length() > longest_word.length()) {
                    longest_word = word;
                }
            }
        }

        return longest_word;
    }
};