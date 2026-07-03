#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>

class LongestWord {
private:
    std::vector<std::string> word_list;

    // Helper function to convert a string to lowercase
    std::string toLower(const std::string& s) {
        std::string result;
        for (char c : s) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
        return result;
    }

    // Helper function to remove punctuation from a string
    std::string removePunctuation(const std::string& s) {
        std::string result;
        for (char c : s) {
            if (!std::ispunct(static_cast<unsigned char>(c))) {
                result += c;
            }
        }
        return result;
    }

public:
    LongestWord() {}

    void add_word(const std::string& word) {
        word_list.push_back(word);
    }

    std::string find_longest_word(const std::string& sentence) {
        if (word_list.empty()) {
            return "";
        }

        // Convert the entire sentence to lowercase
        std::string lower_sentence = toLower(sentence);

        // Remove punctuation from the lowercase sentence
        std::string cleaned_sentence = removePunctuation(lower_sentence);

        // Split the cleaned sentence into words
        std::istringstream iss(cleaned_sentence);
        std::string word;
        std::vector<std::string> words;
        while (iss >> word) {
            words.push_back(word);
        }

        std::string longest_word = "";

        // Find the longest word that exists in the word_list
        for (const auto& w : words) {
            if (std::find(word_list.begin(), word_list.end(), w) != word_list.end()) {
                if (w.length() > longest_word.length()) {
                    longest_word = w;
                }
            }
        }

        return longest_word;
    }
};