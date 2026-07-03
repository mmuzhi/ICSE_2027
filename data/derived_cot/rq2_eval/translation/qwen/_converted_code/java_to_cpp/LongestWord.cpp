#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <locale>
#include <codecvt>
#include <iostream>

class LongestWord {
public:
    std::vector<std::string> wordList;

    void add_word(const std::string& word) {
        wordList.push_back(word);
    }

    std::string find_longest_word(const std::string& sentence) {
        std::string longestWord = "";
        std::string sentence_lower = sentence;
        // Convert to lowercase
        for (char& c : sentence_lower) {
            c = std::tolower(c, std::locale());
        }
        // Remove punctuation
        std::string punct = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
        for (char p : punct) {
            size_t pos = sentence_lower.find(p);
            while (pos != std::string::npos) {
                sentence_lower.erase(pos, 1);
                pos = sentence_lower.find(p);
            }
        }
        // Split the sentence into words
        std::istringstream iss(sentence_lower);
        std::string word;
        while (iss >> word) {
            // Check if word is in wordList and longer than current longest
            if (std::find(wordList.begin(), wordList.end(), word) != wordList.end() &&
                word.length() > longestWord.length()) {
                longestWord = word;
            }
        }
        return longestWord;
    }
};

int main() {
    LongestWord longestWord;
    longestWord.add_word("A");
    longestWord.add_word("aM");
    std::cout << longestWord.find_longest_word("I am a student.") << std::endl;
    return 0;
}