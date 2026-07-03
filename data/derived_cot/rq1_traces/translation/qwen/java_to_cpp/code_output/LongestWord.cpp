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

    void addWord(const std::string& word) {
        wordList.push_back(word);
    }

    std::string findLongestWord(const std::string& sentence) {
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
    longestWord.addWord("A");
    longestWord.addWord("aM");
    std::cout << longestWord.findLongestWord("I am a student.") << std::endl;
    return 0;
}