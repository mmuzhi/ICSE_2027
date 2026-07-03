#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cstddef>

class LongestWord {
private:
    std::vector<std::string> word_list;

public:
    // Constructor: initialize empty word list
    LongestWord() {}

    // Add a word to the list
    void add_word(const std::string& word) {
        word_list.push_back(word);
    }

    // Find the longest word in the sentence that exists in word_list
    std::string find_longest_word(const std::string& sentence) {
        // Step 1: convert sentence to lowercase
        std::string lower_sentence = sentence;
        std::transform(lower_sentence.begin(), lower_sentence.end(), lower_sentence.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        // Step 2: remove all punctuation characters
        std::string clean;
        for (char ch : lower_sentence) {
            if (!std::ispunct(static_cast<unsigned char>(ch))) {
                clean.push_back(ch);
            }
        }

        // Step 3: split by space, preserving empty tokens (re.split(' ', ...) behavior)
        std::istringstream iss(clean);
        std::string token;
        std::string longest_word = "";

        while (std::getline(iss, token, ' ')) {
            // Check if token is in word_list and longer than current longest
            if (!token.empty() &&
                std::find(word_list.begin(), word_list.end(), token) != word_list.end() &&
                token.length() > longest_word.length()) {
                longest_word = token;
            }
        }

        return longest_word;
    }
};