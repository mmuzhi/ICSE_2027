#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>

class LongestWord {
private:
    std::vector<std::string> word_list;

    static bool is_punctuation(char c) {
        static const std::string punct = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        return punct.find(c) != std::string::npos;
    }

public:
    LongestWord() {}

    void add_word(const std::string& word) {
        word_list.push_back(word);
    }

    std::string find_longest_word(const std::string& sentence) {
        std::string longest_word;
        std::string s = sentence;
        // Convert to lowercase
        for (char& c : s) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        // Remove punctuation
        s.erase(std::remove_if(s.begin(), s.end(), is_punctuation), s.end());
        // Split by space (matching re.split(' ', sentence) — preserves empty tokens)
        std::vector<std::string> words;
        std::string current;
        for (char c : s) {
            if (c == ' ') {
                words.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        words.push_back(current);
        // Build set for membership lookup
        std::set<std::string> word_set(word_list.begin(), word_list.end());
        // Find longest word present in word_list
        for (const std::string& word : words) {
            if (word_set.count(word) && word.length() > longest_word.length()) {
                longest_word = word;
            }
        }
        return longest_word;
    }
};