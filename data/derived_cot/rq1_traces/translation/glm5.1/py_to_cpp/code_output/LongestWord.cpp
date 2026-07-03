#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class LongestWord {
private:
    std::vector<std::string> word_list;

public:
    LongestWord() = default;

    void add_word(const std::string& word) {
        word_list.push_back(word);
    }

    std::string find_longest_word(std::string sentence) {
        std::string longest_word = "";
        
        // Convert to lowercase
        std::transform(sentence.begin(), sentence.end(), sentence.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        
        // Remove punctuation
        std::string no_punct;
        for (char c : sentence) {
            if (!std::ispunct(static_cast<unsigned char>(c))) {
                no_punct += c;
            }
        }
        
        // Split by space
        std::vector<std::string> words;
        std::string current_word;
        for (char c : no_punct) {
            if (c == ' ') {
                words.push_back(current_word);
                current_word.clear();
            } else {
                current_word += c;
            }
        }
        words.push_back(current_word);
        
        // Find longest word
        for (const std::string& word : words) {
            if (std::find(word_list.begin(), word_list.end(), word) != word_list.end()) {
                if (word.length() > longest_word.length()) {
                    longest_word = word;
                }
            }
        }
        
        return longest_word;
    }
};